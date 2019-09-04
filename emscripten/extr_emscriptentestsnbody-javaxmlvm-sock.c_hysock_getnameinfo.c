#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hysockaddr_t ;
struct TYPE_7__ {int /*<<< orphan*/  h_name; } ;
struct TYPE_6__ {scalar_t__ sin_family; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_2__ OSSOCKADDR ;
typedef  TYPE_3__ OSHOSTENT ;
typedef  int I_32 ;

/* Variables and functions */
 int HYPORT_ERROR_SOCKET_UNIX_TRYAGAIN ; 
 int /*<<< orphan*/  HYSOCKDEBUGH (char*,int) ; 
 int MAX_RETRIES ; 
 scalar_t__ OS_AF_INET4 ; 
 int /*<<< orphan*/  findError (int) ; 
 int hyerror_set_last_error (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

I_32 hysock_getnameinfo (hysockaddr_t in_addr, I_32 sockaddr_size, char *name, 
                         I_32 name_length, int flags)
{
    
    /* If we have the IPv6 functions available we will call them, otherwise we'll call the IPv4 function */
#if defined(IPv6_FUNCTION_SUPPORT)
    int rc = 0;
    rc =
    getnameinfo ((OSADDR *) & in_addr->addr, sizeof (in_addr->addr), name,
                 name_length, NULL, 0, flags);
    if (rc != 0)
    {
        rc = errno;
        HYSOCKDEBUG ("<gethostbyaddr failed, err=%d>\n", rc);
        return portLibrary->error_set_last_error (portLibrary, rc,
                                                  findError (rc));
    }
    return 0;
#else /* IPv6_FUNCTION_SUPPORT */
#if !HOSTENT_DATA_R
    OSHOSTENT *result;
#endif
    
#if GLIBC_R||OTHER_R
    BOOLEAN allocBuffer = FALSE;
#endif
    int herr = 0;
    int i = 0;
    int rc = 0;
    int length;
    OSSOCKADDR *addr;
#if HOSTENT_DATA_R||GLIBC_R||OTHER_R||NO_R
    PortlibPTBuffers_t ptBuffers;
#endif /* HOSTENT_DATA_R || GLIBC_R || OTHER_R || NO_R */
    addr = (OSSOCKADDR *) & in_addr->addr;
    if (addr->sin_family == OS_AF_INET4)
    {
        length = 4;
    }
    else
    {
        length = 16;
    }
#if HOSTENT_DATA_R||GLIBC_R||OTHER_R||NO_R
    ptBuffers = hyport_tls_get ();
    if (NULL == ptBuffers)
    {
        return HYPORT_ERROR_SOCKET_SYSTEMFULL;
    }
#define hostentBuffer (&ptBuffers->hostent)
#endif /* HOSTENT_DATA_R || GLIBC_R || OTHER_R || NO_R */
    /* one of several threadsafe gethostbyaddr calls must be made depending on the current platform */
    /* if there is a transient error (HYPORT_ERROR_SOCKET_UNIX_TRYAGAIN), try making the call again */
    for (i = 0; i < MAX_RETRIES; i++)
    {
#if HOSTENT_DATA_R
#define dataBuffer (ptBuffers->hostent_data)
        if (!dataBuffer)
        {
            dataBuffer =
            portLibrary->mem_allocate_memory (portLibrary,
                                              sizeof (OSHOSTENT_DATA));
            if (!dataBuffer)
            {
                return HYPORT_ERROR_SOCKET_SYSTEMFULL;
            }
        }
        herr =
        gethostbyaddr_r (&addr->sin_addr, length, addr->sin_family,
                         hostentBuffer, dataBuffer);
#undef dataBuffer
#elif ORIGINAL_R || NO_R
#if NO_R
        MUTEX_ENTER (hostentLock);
#endif
        result = gethostbyaddr (&addr->sin_addr, length, addr->sin_family);
#if NO_R
        if (result)
        {
            herr = copy_hostent (result, &ptBuffers);
        }
        MUTEX_EXIT (hostentLock);
        if (herr != 0)
        {
            return herr;
        }
#endif
        herr = h_errno;
#elif GLIBC_R || OTHER_R
#define buffer (ptBuffers->gethostBuffer)
#define bufferSize (ptBuffers->gethostBufferSize)
        if (!buffer)
        {
            bufferSize = GET_HOST_BUFFER_SIZE;
        }
        while (TRUE)
        {
            if (allocBuffer == TRUE || !buffer)
            {
                /* The buffer is allocated bufferSize + EXTRA_SPACE, while gethostby*_r is only aware of bufferSize
                 * because there seems to be a bug on Linux 386 where gethostbyname_r writes past the end of the
                 * buffer.  This bug has not been observed on other platforms, but EXTRA_SPACE is added anyway as a precaution.*/
                buffer = XMLVM_ATOMIC_MALLOC(bufferSize + EXTRA_SPACE);
                if (!buffer)
                {
                    return HYPORT_ERROR_SOCKET_SYSTEMFULL;
                }
                allocBuffer = FALSE;
            }
#if GLIBC_R
            gethostbyaddr_r ((char *) &addr->sin_addr, length, addr->sin_family,
                             hostentBuffer, buffer, bufferSize, &result, &herr);
#elif OTHER_R
            result =
            gethostbyaddr_r ((char *) &addr->sin_addr, length,
                             addr->sin_family, hostentBuffer, buffer,
                             bufferSize, &herr);
#endif /* GLIBC_R */
            /* allocate more space if the buffer is too small */
            if (errno == ERANGE || herr == ERANGE)
            {
                XMLVM_FREE(buffer);
                bufferSize *= 2;
                allocBuffer = TRUE;
            }
            else
            {
                break;
            }
        }
#undef buffer
#undef bufferSize
#endif
        if (herr != HYPORT_ERROR_SOCKET_UNIX_TRYAGAIN)
        {
            break;
        }
    }
#if HOSTENT_DATA_R
    if (herr != 0)
    {
        herr = h_errno;
        HYSOCKDEBUGH ("<gethostbyaddr failed, err=%d>\n", herr);
        return portLibrary->error_set_last_error (portLibrary, herr,
                                                  findHostError (herr));
    }
#else
    if (result == NULL)
    {
        HYSOCKDEBUGH ("<gethostbyaddr failed, err=%d>\n", herr);
        return hyerror_set_last_error(herr, findError(herr));
    }
#endif
    else
    {
        memset (name, 0, sizeof (char) * name_length);
#if HOSTENT_DATA_R||NO_R
        strcpy (name, hostentBuffer->h_name);
#else
        strcpy (name, result->h_name);
#endif
    }
#if HOSTENT_DATA_R||GLIBC_R||OTHER_R
#undef hostentBuffer
#endif /*HOSTENT_DATA_R || GLIBC_R || OTHER_R */
    return 0;
#endif /* IPv6_FUNCTION_SUPPORT */
    
}