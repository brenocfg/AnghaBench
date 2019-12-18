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
struct seq_file {scalar_t__ count; scalar_t__ from; int size; void* buf; TYPE_1__* op; scalar_t__ index; scalar_t__ version; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int (* show ) (struct seq_file*,void*) ;int /*<<< orphan*/  (* stop ) (struct seq_file*,void*) ;void* (* next ) (struct seq_file*,void*,scalar_t__*) ;void* (* start ) (struct seq_file*,scalar_t__*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* stub1 (struct seq_file*,scalar_t__*) ; 
 int stub2 (struct seq_file*,void*) ; 
 void* stub3 (struct seq_file*,void*,scalar_t__*) ; 
 int /*<<< orphan*/  stub4 (struct seq_file*,void*) ; 
 int /*<<< orphan*/  stub5 (struct seq_file*,void*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int traverse(struct seq_file *m, loff_t offset)
{
	loff_t pos = 0, index;
	int error = 0;
	void *p;

	m->version = 0;
	index = 0;
	m->count = m->from = 0;
	if (!offset) {
		m->index = index;
		return 0;
	}
	if (!m->buf) {
		m->buf = kmalloc(m->size = PAGE_SIZE, GFP_KERNEL);
		if (!m->buf)
			return -ENOMEM;
	}
	p = m->op->start(m, &index);
	while (p) {
		error = PTR_ERR(p);
		if (IS_ERR(p))
			break;
		error = m->op->show(m, p);
		if (error < 0)
			break;
		if (unlikely(error)) {
			error = 0;
			m->count = 0;
		}
		if (m->count == m->size)
			goto Eoverflow;
		if (pos + m->count > offset) {
			m->from = offset - pos;
			m->count -= m->from;
			m->index = index;
			break;
		}
		pos += m->count;
		m->count = 0;
		if (pos == offset) {
			index++;
			m->index = index;
			break;
		}
		p = m->op->next(m, p, &index);
	}
	m->op->stop(m, p);
	m->index = index;
	return error;

Eoverflow:
	m->op->stop(m, p);
	kfree(m->buf);
	m->buf = kmalloc(m->size <<= 1, GFP_KERNEL);
	return !m->buf ? -ENOMEM : -EAGAIN;
}