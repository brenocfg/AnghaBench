#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Curl_dns_entry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  aprintf (char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  data_key ; 
 TYPE_1__* data_node ; 
 int /*<<< orphan*/  fake_ai () ; 

__attribute__((used)) static CURLcode create_node(void)
{
  data_key = aprintf("%s:%d", "dummy", 0);
  if(!data_key)
    return CURLE_OUT_OF_MEMORY;

  data_node = calloc(1, sizeof(struct Curl_dns_entry));
  if(!data_node)
    return CURLE_OUT_OF_MEMORY;

  data_node->addr = fake_ai();
  if(!data_node->addr)
    return CURLE_OUT_OF_MEMORY;

  return CURLE_OK;
}