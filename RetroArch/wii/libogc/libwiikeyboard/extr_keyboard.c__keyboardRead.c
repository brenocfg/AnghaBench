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
struct _reent {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {size_t head; size_t tail; char* buf; } ;

/* Variables and functions */
 TYPE_1__ _keyBuffer ; 
 int /*<<< orphan*/  _readKey_cb (char) ; 

__attribute__((used)) static ssize_t _keyboardRead(struct _reent *r, void *unused, char *ptr, size_t len)
{
	ssize_t count = len;
	while ( count > 0 ) {
		if (_keyBuffer.head != _keyBuffer.tail) {
			char key = _keyBuffer.buf[_keyBuffer.head];
			*ptr++ = key;
			if (_readKey_cb != NULL) _readKey_cb(key);
			_keyBuffer.head++;
			count--;
		}
	}
	return len;
}