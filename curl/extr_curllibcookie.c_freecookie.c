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
struct Cookie {struct Cookie* version; struct Cookie* maxage; struct Cookie* value; struct Cookie* name; struct Cookie* spath; struct Cookie* path; struct Cookie* domain; struct Cookie* expirestr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct Cookie*) ; 

__attribute__((used)) static void freecookie(struct Cookie *co)
{
  free(co->expirestr);
  free(co->domain);
  free(co->path);
  free(co->spath);
  free(co->name);
  free(co->value);
  free(co->maxage);
  free(co->version);
  free(co);
}