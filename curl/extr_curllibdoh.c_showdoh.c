#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dohentry {char* ttl; int numaddr; int numcname; TYPE_2__* cname; struct dohaddr* addr; } ;
struct TYPE_3__ {int /*<<< orphan*/ * v6; int /*<<< orphan*/ * v4; } ;
struct dohaddr {scalar_t__ type; TYPE_1__ ip; } ;
struct Curl_easy {int dummy; } ;
struct TYPE_4__ {char* alloc; } ;

/* Variables and functions */
 scalar_t__ DNS_TYPE_A ; 
 scalar_t__ DNS_TYPE_AAAA ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,char*,...) ; 
 int /*<<< orphan*/  msnprintf (char*,size_t,char*,...) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void showdoh(struct Curl_easy *data,
                    struct dohentry *d)
{
  int i;
  infof(data, "TTL: %u seconds\n", d->ttl);
  for(i = 0; i < d->numaddr; i++) {
    struct dohaddr *a = &d->addr[i];
    if(a->type == DNS_TYPE_A) {
      infof(data, "DOH A: %u.%u.%u.%u\n",
            a->ip.v4[0], a->ip.v4[1],
            a->ip.v4[2], a->ip.v4[3]);
    }
    else if(a->type == DNS_TYPE_AAAA) {
      int j;
      char buffer[128];
      char *ptr;
      size_t len;
      msnprintf(buffer, 128, "DOH AAAA: ");
      ptr = &buffer[10];
      len = 118;
      for(j = 0; j < 16; j += 2) {
        size_t l;
        msnprintf(ptr, len, "%s%02x%02x", j?":":"", d->addr[i].ip.v6[j],
                  d->addr[i].ip.v6[j + 1]);
        l = strlen(ptr);
        len -= l;
        ptr += l;
      }
      infof(data, "%s\n", buffer);
    }
  }
  for(i = 0; i < d->numcname; i++) {
    infof(data, "CNAME: %s\n", d->cname[i].alloc);
  }
}