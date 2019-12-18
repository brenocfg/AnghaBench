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
struct Cookie {int /*<<< orphan*/  creationtime; int /*<<< orphan*/  httponly; int /*<<< orphan*/  livecookie; int /*<<< orphan*/  secure; int /*<<< orphan*/  tailmatch; int /*<<< orphan*/  expires; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE (int /*<<< orphan*/ ) ; 
 struct Cookie* calloc (int,int) ; 
 int /*<<< orphan*/  domain ; 
 int /*<<< orphan*/  expirestr ; 
 int /*<<< orphan*/  freecookie (struct Cookie*) ; 
 int /*<<< orphan*/  maxage ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  spath ; 
 int /*<<< orphan*/  value ; 
 int /*<<< orphan*/  version ; 

__attribute__((used)) static struct Cookie *dup_cookie(struct Cookie *src)
{
  struct Cookie *d = calloc(sizeof(struct Cookie), 1);
  if(d) {
    CLONE(expirestr);
    CLONE(domain);
    CLONE(path);
    CLONE(spath);
    CLONE(name);
    CLONE(value);
    CLONE(maxage);
    CLONE(version);
    d->expires = src->expires;
    d->tailmatch = src->tailmatch;
    d->secure = src->secure;
    d->livecookie = src->livecookie;
    d->httponly = src->httponly;
    d->creationtime = src->creationtime;
  }
  return d;

  fail:
  freecookie(d);
  return NULL;
}