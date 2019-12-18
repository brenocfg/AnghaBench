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
struct p9_client {scalar_t__ max_tag; int /*<<< orphan*/ * tagpool; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * p9_idpool_create () ; 
 int /*<<< orphan*/  p9_idpool_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p9_tag_init(struct p9_client *c)
{
	int err = 0;

	c->tagpool = p9_idpool_create();
	if (IS_ERR(c->tagpool)) {
		err = PTR_ERR(c->tagpool);
		c->tagpool = NULL;
		goto error;
	}

	p9_idpool_get(c->tagpool); /* reserve tag 0 */

	c->max_tag = 0;
error:
	return err;
}