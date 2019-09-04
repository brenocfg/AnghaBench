#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray ;
typedef  int /*<<< orphan*/  java_lang_String ;
typedef  size_t U_32 ;
typedef  int /*<<< orphan*/ * JAVA_OBJECT ;
typedef  scalar_t__ JAVA_ARRAY_BYTE ;
typedef  int /*<<< orphan*/  IPv6ANY ;
typedef  int /*<<< orphan*/  IPv4ANY ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/ * JAVA_NULL ; 
 int /*<<< orphan*/ * __NEW_java_net_InetAddress () ; 
 scalar_t__ harmony_supports_ipv6 () ; 
 int /*<<< orphan*/  java_net_InetAddress___INIT____byte_1ARRAY_java_lang_String (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * java_net_InetAddress_getByAddress___java_lang_String_byte_1ARRAY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newJavaByteArray (scalar_t__*,size_t) ; 
 int /*<<< orphan*/  preferIPv4Stack () ; 
 scalar_t__ preferIPv6Addresses () ; 
 int /*<<< orphan*/ * xmlvm_create_java_string (char const*) ; 

JAVA_OBJECT newJavaNetInetAddressGenericBS (JAVA_ARRAY_BYTE* address, U_32 length,
                                const char* hostName, U_32 scope_id)
{
    org_xmlvm_runtime_XMLVMArray* byte_array;
    java_lang_String* aString;
    BOOLEAN isAnyAddress = 1;
    static JAVA_ARRAY_BYTE IPv4ANY[4] = { 0, 0, 0, 0 };
    static JAVA_ARRAY_BYTE IPv6ANY[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    U_32 i = 0;
    JAVA_OBJECT result = JAVA_NULL;
    
    aString = xmlvm_create_java_string(hostName);
    
    /* check if the address being returned is the any address.  If so we need to check the prefer flags to see how it should be returned
     (either as IPv4 Any or IPv6 ANY) */
    
    if (harmony_supports_ipv6 ())
    {
        /* Figure out if it is the any address */
        for (i = 0; i < length; i++)
        {
            if (address[i] != 0)
            {
                isAnyAddress = 0;
                break;
            }
        }
    }
    else
    {
        /* just do what we used to do without checking */
        isAnyAddress = 0;
    }
    
    /* If it is the any address then set up to return appropriately based on the flags */
    if (isAnyAddress)
    {
        if ((!preferIPv4Stack ()) && (preferIPv6Addresses ()))
        {
            if ((byte_array =
                 newJavaByteArray (IPv6ANY, sizeof (IPv6ANY))) == NULL)
            {
                return NULL;
            }
        }
        else
        {
            if ((byte_array =
                 newJavaByteArray (IPv4ANY, sizeof (IPv4ANY))) == NULL)
            {
                return NULL;
            }
        }
    }
    else
    {
        /* not any so just set up to return the address normally */
        if ((byte_array = newJavaByteArray (address, length)) == NULL)
        {
            return NULL;
        }
    }
    
    if (harmony_supports_ipv6 ())
    {
#ifdef SUPPORTS_SCOPED_GETBYADDR
        if (scope_id != 0) {
            result = java_net_InetAddress_getByAddress___java_lang_String_byte_1ARRAY_int(aString, byte_array, scope_id);
        }
        else {
#endif
            result = java_net_InetAddress_getByAddress___java_lang_String_byte_1ARRAY(aString, byte_array);

#ifdef SUPPORTS_SCOPED_GETBYADDR
        }
#endif
        
    }
    else
    {
        result = __NEW_java_net_InetAddress();
        java_net_InetAddress___INIT____byte_1ARRAY_java_lang_String(result, byte_array, aString);
        //return result;
    }
    
    return result;
}