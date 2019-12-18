#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int XML_LChar ;
struct TYPE_3__ {int major; int minor; int micro; } ;
typedef  TYPE_1__ XML_Expat_Version ;

/* Variables and functions */
 int const ASCII_0 ; 
 int const ASCII_9 ; 
 int /*<<< orphan*/  ASCII_PERIOD ; 
 int XML_FALSE ; 
 int XML_TRUE ; 

__attribute__((used)) static int
parse_version(const XML_LChar *version_text,
              XML_Expat_Version *version_struct)
{
    while (*version_text != 0x00) {
        if (*version_text >= ASCII_0 && *version_text <= ASCII_9)
            break;
        version_text++;
    }
    if (*version_text == 0x00)
        return XML_FALSE;

    /* version_struct->major = strtoul(version_text, 10, &version_text) */
    version_struct->major = 0;
    while (*version_text >= ASCII_0 && *version_text <= ASCII_9) {
        version_struct->major =
            10 * version_struct->major + (*version_text++ - ASCII_0);
    }
    if (*version_text++ != ASCII_PERIOD)
        return XML_FALSE;

    /* Now for the minor version number */
    version_struct->minor = 0;
    while (*version_text >= ASCII_0 && *version_text <= ASCII_9) {
        version_struct->minor =
            10 * version_struct->minor + (*version_text++ - ASCII_0);
    }
    if (*version_text++ != ASCII_PERIOD)
        return XML_FALSE;

    /* Finally the micro version number */
    version_struct->micro = 0;
    while (*version_text >= ASCII_0 && *version_text <= ASCII_9) {
        version_struct->micro =
            10 * version_struct->micro + (*version_text++ - ASCII_0);
    }
    if (*version_text != 0x00)
        return XML_FALSE;
    return XML_TRUE;
}