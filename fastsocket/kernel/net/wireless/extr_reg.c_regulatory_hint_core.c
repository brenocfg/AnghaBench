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
struct regulatory_request {char* alpha2; int /*<<< orphan*/  initiator; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_REGDOM_SET_BY_CORE ; 
 struct regulatory_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_regulatory_request (struct regulatory_request*) ; 

__attribute__((used)) static int regulatory_hint_core(const char *alpha2)
{
	struct regulatory_request *request;

	request = kzalloc(sizeof(struct regulatory_request), GFP_KERNEL);
	if (!request)
		return -ENOMEM;

	request->alpha2[0] = alpha2[0];
	request->alpha2[1] = alpha2[1];
	request->initiator = NL80211_REGDOM_SET_BY_CORE;

	queue_regulatory_request(request);

	return 0;
}