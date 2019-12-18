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
struct TYPE_2__ {int /*<<< orphan*/ * node; } ;
struct watch_adapter {int /*<<< orphan*/ * token; TYPE_1__ watch; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  free_watch_adapter (struct watch_adapter*) ; 
 void* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct watch_adapter* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct watch_adapter *alloc_watch_adapter(const char *path,
						 const char *token)
{
	struct watch_adapter *watch;

	watch = kzalloc(sizeof(*watch), GFP_KERNEL);
	if (watch == NULL)
		goto out_fail;

	watch->watch.node = kstrdup(path, GFP_KERNEL);
	if (watch->watch.node == NULL)
		goto out_free;

	watch->token = kstrdup(token, GFP_KERNEL);
	if (watch->token == NULL)
		goto out_free;

	return watch;

out_free:
	free_watch_adapter(watch);

out_fail:
	return NULL;
}