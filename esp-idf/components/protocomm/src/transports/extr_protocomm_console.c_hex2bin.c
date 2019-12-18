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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sscanf (char const*,char*,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static ssize_t hex2bin(const char *hexstr, uint8_t *bytes)
{
    size_t hexstrLen = strlen(hexstr);
    ssize_t bytesLen = hexstrLen / 2;

    int count = 0;
    const char *pos = hexstr;

    for(count = 0; count < bytesLen; count++) {
        sscanf(pos, "%2hhx", &bytes[count]);
        pos += 2;
    }

    return bytesLen;
}