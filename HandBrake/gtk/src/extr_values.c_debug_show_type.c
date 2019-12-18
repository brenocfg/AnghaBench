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
typedef  char gchar ;
typedef  scalar_t__ GhbType ;

/* Variables and functions */
 scalar_t__ GHB_ARRAY ; 
 scalar_t__ GHB_BOOL ; 
 scalar_t__ GHB_DICT ; 
 scalar_t__ GHB_DOUBLE ; 
 scalar_t__ GHB_INT ; 
 scalar_t__ GHB_STRING ; 
 int /*<<< orphan*/  g_debug (char*,char const*) ; 

void
debug_show_type(GhbType tp)
{
    const gchar *str = "unknown";
    if (tp == GHB_STRING)
    {
        str ="string";
    }
    else if (tp == GHB_INT)
    {
        str ="int";
    }
    else if (tp == GHB_DOUBLE)
    {
        str ="double";
    }
    else if (tp == GHB_BOOL)
    {
        str ="bool";
    }
    else if (tp == GHB_ARRAY)
    {
        str ="array";
    }
    else if (tp == GHB_DICT)
    {
        str ="dict";
    }
    g_debug("Type %s", str);
}