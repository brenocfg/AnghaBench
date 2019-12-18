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
typedef  int /*<<< orphan*/  DOHcode ;

/* Variables and functions */
 int /*<<< orphan*/  DOH_DNS_BAD_LABEL ; 
 int /*<<< orphan*/  DOH_DNS_OUT_OF_RANGE ; 
 int /*<<< orphan*/  DOH_OK ; 

__attribute__((used)) static DOHcode skipqname(unsigned char *doh, size_t dohlen,
                         unsigned int *indexp)
{
  unsigned char length;
  do {
    if(dohlen < (*indexp + 1))
      return DOH_DNS_OUT_OF_RANGE;
    length = doh[*indexp];
    if((length & 0xc0) == 0xc0) {
      /* name pointer, advance over it and be done */
      if(dohlen < (*indexp + 2))
        return DOH_DNS_OUT_OF_RANGE;
      *indexp += 2;
      break;
    }
    if(length & 0xc0)
      return DOH_DNS_BAD_LABEL;
    if(dohlen < (*indexp + 1 + length))
      return DOH_DNS_OUT_OF_RANGE;
    *indexp += 1 + length;
  } while(length);
  return DOH_OK;
}