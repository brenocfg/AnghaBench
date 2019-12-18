#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  resource; int /*<<< orphan*/  context; TYPE_1__* dispatcher; } ;
typedef  TYPE_2__ ebb_request_extras ;
struct TYPE_8__ {scalar_t__ data; } ;
typedef  TYPE_3__ ebb_request ;
struct TYPE_6__ {int /*<<< orphan*/  context; int /*<<< orphan*/  (* parse ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  URI_QUERY_STRING ; 
 int /*<<< orphan*/  on_request_headers_complete (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_request_query_string(ebb_request* request, const char* at, size_t length)
{
	on_request_headers_complete(request); // resolve uri first
	ebb_request_extras* request_extras = (ebb_request_extras*)request->data;
	if (request_extras->dispatcher && request_extras->dispatcher->parse)
		request_extras->context = request_extras->dispatcher->parse(request_extras->dispatcher->context, request_extras->context, request_extras->resource, at, length, URI_QUERY_STRING, 0);
}