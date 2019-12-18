#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dohentry {size_t numaddr; struct dohaddr* addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  v4; } ;
struct dohaddr {TYPE_1__ ip; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  DOHcode ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_TYPE_A ; 
 size_t DOH_MAX_ADDR ; 
 int /*<<< orphan*/  DOH_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static DOHcode store_a(unsigned char *doh, int index, struct dohentry *d)
{
  /* silently ignore addresses over the limit */
  if(d->numaddr < DOH_MAX_ADDR) {
    struct dohaddr *a = &d->addr[d->numaddr];
    a->type = DNS_TYPE_A;
    memcpy(&a->ip.v4, &doh[index], 4);
    d->numaddr++;
  }
  return DOH_OK;
}