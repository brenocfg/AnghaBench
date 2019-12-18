#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t cursor; scalar_t__ uri; } ;
typedef  TYPE_1__ ebb_request_extras ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_2__ ebb_request ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 

__attribute__((used)) static void on_request_path(ebb_request* request, const char* at, size_t length)
{
	ebb_request_extras* request_extras = (ebb_request_extras*)request->data;
	if (length + request_extras->cursor < 256)
		memcpy(request_extras->uri + request_extras->cursor, at, length);
	request_extras->cursor += length;
}