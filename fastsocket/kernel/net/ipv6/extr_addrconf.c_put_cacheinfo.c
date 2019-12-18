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
typedef  void* u32 ;
struct sk_buff {int dummy; } ;
struct ifa_cacheinfo {void* ifa_valid; void* ifa_prefered; void* tstamp; void* cstamp; } ;
typedef  int /*<<< orphan*/  ci ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IFA_CACHEINFO ; 
 int /*<<< orphan*/  INITIAL_JIFFIES ; 
 int TIME_DELTA (unsigned long,int /*<<< orphan*/ ) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct ifa_cacheinfo*) ; 

__attribute__((used)) static int put_cacheinfo(struct sk_buff *skb, unsigned long cstamp,
			 unsigned long tstamp, u32 preferred, u32 valid)
{
	struct ifa_cacheinfo ci;

	ci.cstamp = (u32)(TIME_DELTA(cstamp, INITIAL_JIFFIES) / HZ * 100
			+ TIME_DELTA(cstamp, INITIAL_JIFFIES) % HZ * 100 / HZ);
	ci.tstamp = (u32)(TIME_DELTA(tstamp, INITIAL_JIFFIES) / HZ * 100
			+ TIME_DELTA(tstamp, INITIAL_JIFFIES) % HZ * 100 / HZ);
	ci.ifa_prefered = preferred;
	ci.ifa_valid = valid;

	return nla_put(skb, IFA_CACHEINFO, sizeof(ci), &ci);
}