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
struct sun_entry {int /*<<< orphan*/ * location_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  sun_locations2amd (char*,size_t,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sun_nfs2amd(char *dest,
	    size_t destlen,
	    const char *key,
	    const struct sun_entry *s_entry)
{
  if (s_entry->location_list != NULL) {
    /* write out the list of mountpoint locations */
    sun_locations2amd(dest, destlen, key, s_entry->location_list);
  }
}