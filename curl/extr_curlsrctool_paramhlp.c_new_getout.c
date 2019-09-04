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
struct getout {int /*<<< orphan*/  flags; struct getout* next; } ;
struct OperationConfig {int /*<<< orphan*/  default_node_flags; struct getout* url_last; struct getout* url_list; } ;

/* Variables and functions */
 struct getout* calloc (int,int) ; 

struct getout *new_getout(struct OperationConfig *config)
{
  struct getout *node = calloc(1, sizeof(struct getout));
  struct getout *last = config->url_last;
  if(node) {
    /* append this new node last in the list */
    if(last)
      last->next = node;
    else
      config->url_list = node; /* first node */

    /* move the last pointer */
    config->url_last = node;

    node->flags = config->default_node_flags;
  }
  return node;
}