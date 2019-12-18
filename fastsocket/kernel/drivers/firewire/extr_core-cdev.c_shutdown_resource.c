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
struct client_resource {int /*<<< orphan*/  (* release ) (struct client*,struct client_resource*) ;} ;
struct client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  client_put (struct client*) ; 
 int /*<<< orphan*/  stub1 (struct client*,struct client_resource*) ; 

__attribute__((used)) static int shutdown_resource(int id, void *p, void *data)
{
	struct client_resource *r = p;
	struct client *client = data;

	r->release(client, r);
	client_put(client);

	return 0;
}