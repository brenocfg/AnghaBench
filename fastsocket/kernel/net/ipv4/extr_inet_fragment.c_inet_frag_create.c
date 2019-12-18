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
struct netns_frags {int dummy; } ;
struct inet_frags {int dummy; } ;
struct inet_frag_queue {int dummy; } ;

/* Variables and functions */
 struct inet_frag_queue* inet_frag_alloc (struct netns_frags*,struct inet_frags*,void*) ; 
 struct inet_frag_queue* inet_frag_intern (struct netns_frags*,struct inet_frag_queue*,struct inet_frags*,void*) ; 

__attribute__((used)) static struct inet_frag_queue *inet_frag_create(struct netns_frags *nf,
		struct inet_frags *f, void *arg)
{
	struct inet_frag_queue *q;

	q = inet_frag_alloc(nf, f, arg);
	if (q == NULL)
		return NULL;

	return inet_frag_intern(nf, q, f, arg);
}