#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U_32 ;
struct TYPE_6__ {char* h_name; int /*<<< orphan*/ ** h_addr_list; int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addrtype; void* h_aliases; } ;
struct TYPE_5__ {char* gethostBuffer; int gethostBufferSize; TYPE_2__ hostent; } ;
typedef  TYPE_1__* PortlibPTBuffers_t ;
typedef  TYPE_2__ OSHOSTENT ;
typedef  int /*<<< orphan*/  I_32 ;

/* Variables and functions */
 int /*<<< orphan*/  HYPORT_ERROR_SOCKET_SYSTEMFULL ; 
 char* XMLVM_ATOMIC_MALLOC (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static I_32 copy_hostent (OSHOSTENT * source, PortlibPTBuffers_t * ptBuffers)
{
    int h_len = strlen (source->h_name);
    int total = 0;
    int i = 0;
    char *buffer;
    OSHOSTENT *dest = &(*ptBuffers)->hostent;
    /* add trailing NULL, and round off to nearest pointer size */
    h_len = (h_len + 1 + sizeof (void *)) & ~(sizeof (void *) - 1);
    while (source->h_addr_list[i])
        i++;
    total = h_len + ((i + 2) * sizeof (void *)) + (i * sizeof (U_32));
    if (!(*ptBuffers)->gethostBuffer || (*ptBuffers)->gethostBufferSize < total)
    {
        (*ptBuffers)->gethostBuffer = XMLVM_ATOMIC_MALLOC(total);
        if (!(*ptBuffers)->gethostBuffer)
        {
            return HYPORT_ERROR_SOCKET_SYSTEMFULL;
        }
        (*ptBuffers)->gethostBufferSize = total;
    }
    buffer = (*ptBuffers)->gethostBuffer;
    dest->h_name = buffer;
    strcpy (buffer, source->h_name);
    buffer += h_len;
    dest->h_aliases = (void *) buffer;
    *((void **) buffer) = NULL;
    buffer += sizeof (void *);
    dest->h_addrtype = source->h_addrtype;
    dest->h_length = source->h_length;
    dest->h_addr_list = (void *) buffer;
    buffer += (i + 1) * sizeof (void *);
    i = 0;
    while (source->h_addr_list[i])
    {
        dest->h_addr_list[i] = (void *) buffer;
        *((U_32 *) buffer) = *((U_32 *) source->h_addr_list[i]);
        buffer += sizeof (U_32);
        i++;
    }
    dest->h_addr_list[i] = NULL;
    
    return 0;
}