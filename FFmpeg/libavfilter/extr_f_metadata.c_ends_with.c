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
 int FFMAX (int const,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int const) ; 

__attribute__((used)) static int ends_with(MetadataContext *s, const char *value1, const char *value2)
{
    const int len1 = strlen(value1);
    const int len2 = strlen(value2);

    return !strncmp(value1 + FFMAX(len1 - len2, 0), value2, len2);
}