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
struct TYPE_2__ {int /*<<< orphan*/  tail; } ;
struct Curl_multi {TYPE_1__ msglist; } ;
struct Curl_message {int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLM_OK ; 
 int /*<<< orphan*/  Curl_llist_insert_next (TYPE_1__*,int /*<<< orphan*/ ,struct Curl_message*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static CURLMcode multi_addmsg(struct Curl_multi *multi,
                              struct Curl_message *msg)
{
  Curl_llist_insert_next(&multi->msglist, multi->msglist.tail, msg,
                         &msg->list);
  return CURLM_OK;
}