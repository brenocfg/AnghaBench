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
struct GlobalConfig {TYPE_1__* current; } ;
struct TYPE_2__ {struct TYPE_2__* next; } ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int /*<<< orphan*/  CURLSH ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int FALSE ; 
 int /*<<< orphan*/  transfer_per_config (struct GlobalConfig*,TYPE_1__*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static CURLcode create_transfer(struct GlobalConfig *global,
                                CURLSH *share,
                                bool *added)
{
  CURLcode result = CURLE_OK;
  *added = FALSE;
  while(global->current) {
    result = transfer_per_config(global, global->current, share, added);
    if(!result && !*added) {
      /* when one set is drained, continue to next */
      global->current = global->current->next;
      continue;
    }
    break;
  }
  return result;
}