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
struct RDIR {int dummy; } ;

/* Variables and functions */
 struct RDIR* retro_opendir_include_hidden (char const*,int) ; 

struct RDIR *retro_opendir(const char *name)
{
   return retro_opendir_include_hidden(name, false);
}