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

/* Variables and functions */
 int SSL3_VERSION ; 
 int TLS1_1_VERSION ; 
 int TLS1_2_VERSION ; 
 int TLS1_VERSION ; 

__attribute__((used)) static const char* ssl_protocol_to_string(int version)
{
    const char *str;

    if (version == TLS1_2_VERSION)
        str = "TLSv1.2";
    else if (version == TLS1_1_VERSION)
        str = "TLSv1.1";
    else if (version == TLS1_VERSION)
        str = "TLSv1";
    else if (version == SSL3_VERSION)
        str = "SSLv3";
    else
        str = "unknown";

    return str;
}