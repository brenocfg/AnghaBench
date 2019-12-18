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
typedef  int /*<<< orphan*/  MetadataContext ;

/* Variables and functions */
 float FLT_EPSILON ; 
 int sscanf (char const*,char*,float*) ; 

__attribute__((used)) static int greater(MetadataContext *s, const char *value1, const char *value2)
{
    float f1, f2;

    if (sscanf(value1, "%f", &f1) + sscanf(value2, "%f", &f2) != 2)
        return 0;

    return (f2 - f1) < FLT_EPSILON;
}