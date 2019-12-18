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
struct typhoon {TYPE_1__* indexes; } ;
struct TYPE_2__ {int /*<<< orphan*/  respCleared; int /*<<< orphan*/  respReady; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESPONSE_ENTRIES ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int typhoon_num_free (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
typhoon_num_free_resp(struct typhoon *tp)
{
	int respReady = le32_to_cpu(tp->indexes->respReady);
	int respCleared = le32_to_cpu(tp->indexes->respCleared);

	return typhoon_num_free(respReady, respCleared, RESPONSE_ENTRIES);
}