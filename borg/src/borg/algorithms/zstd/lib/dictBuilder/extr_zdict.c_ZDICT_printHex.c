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
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,int) ; 

__attribute__((used)) static void ZDICT_printHex(const void* ptr, size_t length)
{
    const BYTE* const b = (const BYTE*)ptr;
    size_t u;
    for (u=0; u<length; u++) {
        BYTE c = b[u];
        if (c<32 || c>126) c = '.';   /* non-printable char */
        DISPLAY("%c", c);
    }
}