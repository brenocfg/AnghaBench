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
typedef  int gint ;
typedef  char gchar ;

/* Variables and functions */
 char* g_strdup_printf (char*,int,...) ; 
 int /*<<< orphan*/  hb_reduce (int*,int*,double,double) ; 

char *
ghb_get_display_aspect_string(double disp_width, double disp_height)
{
    gchar *str;

    gint iaspect = disp_width * 9 / disp_height;
    if (disp_width > 2 * disp_height)
    {
        str = g_strdup_printf("%.2f:1", disp_width / disp_height);
    }
    else if (iaspect <= 16 && iaspect >= 15)
    {
        str = g_strdup_printf("%.4g:9", disp_width * 9 / disp_height);
    }
    else if (iaspect <= 12 && iaspect >= 11)
    {
        str = g_strdup_printf("%.4g:3", disp_width * 3 / disp_height);
    }
    else
    {
        gint dar_width, dar_height;
        hb_reduce(&dar_width, &dar_height, disp_width, disp_height);
        str = g_strdup_printf("%d:%d", dar_width, dar_height);
    }
    return str;
}