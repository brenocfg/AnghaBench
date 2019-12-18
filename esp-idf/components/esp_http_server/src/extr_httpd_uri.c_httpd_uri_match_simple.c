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
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static bool httpd_uri_match_simple(const char *uri1, const char *uri2, size_t len2)
{
    return strlen(uri1) == len2 &&          // First match lengths
        (strncmp(uri1, uri2, len2) == 0);   // Then match actual URIs
}