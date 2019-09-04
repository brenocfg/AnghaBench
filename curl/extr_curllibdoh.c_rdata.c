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
struct dohentry {int dummy; } ;
typedef  int /*<<< orphan*/  DOHcode ;

/* Variables and functions */
#define  DNS_TYPE_A 130 
#define  DNS_TYPE_AAAA 129 
#define  DNS_TYPE_CNAME 128 
 int /*<<< orphan*/  DOH_DNS_RDATA_LEN ; 
 int /*<<< orphan*/  DOH_OK ; 
 int /*<<< orphan*/  store_a (unsigned char*,int,struct dohentry*) ; 
 int /*<<< orphan*/  store_aaaa (unsigned char*,int,struct dohentry*) ; 
 int /*<<< orphan*/  store_cname (unsigned char*,size_t,int,struct dohentry*) ; 

__attribute__((used)) static DOHcode rdata(unsigned char *doh,
                     size_t dohlen,
                     unsigned short rdlength,
                     unsigned short type,
                     int index,
                     struct dohentry *d)
{
  /* RDATA
     - A (TYPE 1):  4 bytes
     - AAAA (TYPE 28): 16 bytes
     - NS (TYPE 2): N bytes */
  DOHcode rc;

  switch(type) {
  case DNS_TYPE_A:
    if(rdlength != 4)
      return DOH_DNS_RDATA_LEN;
    rc = store_a(doh, index, d);
    if(rc)
      return rc;
    break;
  case DNS_TYPE_AAAA:
    if(rdlength != 16)
      return DOH_DNS_RDATA_LEN;
    rc = store_aaaa(doh, index, d);
    if(rc)
      return rc;
    break;
  case DNS_TYPE_CNAME:
    rc = store_cname(doh, dohlen, index, d);
    if(rc)
      return rc;
    break;
  default:
    /* unsupported type, just skip it */
    break;
  }
  return DOH_OK;
}