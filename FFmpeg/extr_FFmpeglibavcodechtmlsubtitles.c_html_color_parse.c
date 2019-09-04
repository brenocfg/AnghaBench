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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  FFMAX (int /*<<< orphan*/ ,int) ; 
 scalar_t__ av_parse_color (int*,char const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strcspn (char const*,char*) ; 

__attribute__((used)) static int html_color_parse(void *log_ctx, const char *str)
{
    uint8_t rgba[4];
    int nb_sharps = 0;
    while (str[nb_sharps] == '#')
        nb_sharps++;
    str += FFMAX(0, nb_sharps - 1);
    if (av_parse_color(rgba, str, strcspn(str, "\" >"), log_ctx) < 0)
        return -1;
    return rgba[0] | rgba[1] << 8 | rgba[2] << 16;
}