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
struct TYPE_3__ {scalar_t__* (* malloc_fcn ) (int) ;} ;
typedef  TYPE_1__ XML_Memory_Handling_Suite ;
typedef  scalar_t__ XML_Char ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 
 scalar_t__* stub1 (int) ; 

__attribute__((used)) static XML_Char *
copyString(const XML_Char *s,
           const XML_Memory_Handling_Suite *memsuite)
{
    int charsRequired = 0;
    XML_Char *result;

    /* First determine how long the string is */
    while (s[charsRequired] != 0) {
      charsRequired++;
    }
    /* Include the terminator */
    charsRequired++;

    /* Now allocate space for the copy */
    result = memsuite->malloc_fcn(charsRequired * sizeof(XML_Char));
    if (result == NULL)
        return NULL;
    /* Copy the original into place */
    memcpy(result, s, charsRequired * sizeof(XML_Char));
    return result;
}