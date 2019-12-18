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
struct Qdisc_class_hash {int /*<<< orphan*/  hashsize; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  qdisc_class_hash_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qdisc_class_hash_destroy(struct Qdisc_class_hash *clhash)
{
	qdisc_class_hash_free(clhash->hash, clhash->hashsize);
}