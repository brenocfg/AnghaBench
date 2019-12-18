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
 int /*<<< orphan*/  F (char*,unsigned char*,int,int,int,unsigned char*) ; 
 size_t SHA_DIGEST_LEN ; 
 int strlen (char*) ; 

int PasswordHash(char *password, unsigned char *ssid, int ssidlength, unsigned char *output)
{
    if ((strlen(password) > 63) || (ssidlength > 32))
        return 0;

    F(password, ssid, ssidlength, 4096, 1, output);
    F(password, ssid, ssidlength, 4096, 2, &output[SHA_DIGEST_LEN]);
    return 1;
}