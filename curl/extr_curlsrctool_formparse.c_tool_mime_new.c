#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  toolmimekind ;
struct TYPE_4__ {struct TYPE_4__* subparts; struct TYPE_4__* prev; struct TYPE_4__* parent; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ tool_mime ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 

__attribute__((used)) static tool_mime *tool_mime_new(tool_mime *parent, toolmimekind kind)
{
  tool_mime *m = (tool_mime *) calloc(1, sizeof(*m));

  if(m) {
    m->kind = kind;
    m->parent = parent;
    if(parent) {
      m->prev = parent->subparts;
      parent->subparts = m;
    }
  }
  return m;
}