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
struct TYPE_4__ {int size; void* data; } ;
typedef  TYPE_1__ X_SERIAL ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,void*,int) ; 
 void* ZeroMalloc (int) ; 

X_SERIAL *CloneXSerial(X_SERIAL *src)
{
	X_SERIAL *s;
	// Validate arguments
	if (src == NULL)
	{
		return NULL;
	}

	s = ZeroMalloc(sizeof(X_SERIAL));
	s->data = ZeroMalloc(src->size);
	Copy(s->data, src->data, src->size);
	s->size = src->size;

	return s;
}