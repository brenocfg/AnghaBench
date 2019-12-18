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
 scalar_t__ dirent_opendir_cb (char const*,int) ; 
 scalar_t__ retro_vfs_opendir_impl (char const*,int) ; 

struct RDIR *retro_opendir_include_hidden(const char *name, bool include_hidden)
{
   if (dirent_opendir_cb != NULL)
      return (struct RDIR *)dirent_opendir_cb(name, include_hidden);
   return (struct RDIR *)retro_vfs_opendir_impl(name, include_hidden);
}