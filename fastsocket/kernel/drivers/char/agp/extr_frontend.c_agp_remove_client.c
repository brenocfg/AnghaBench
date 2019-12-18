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
struct agp_controller {int /*<<< orphan*/  num_clients; struct agp_client* clients; } ;
struct agp_client {struct agp_client* prev; struct agp_client* next; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int EINVAL ; 
 struct agp_client* agp_find_client_in_controller (struct agp_controller*,int /*<<< orphan*/ ) ; 
 struct agp_controller* agp_find_controller_for_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_remove_seg_from_client (struct agp_client*) ; 
 int /*<<< orphan*/  kfree (struct agp_client*) ; 

int agp_remove_client(pid_t id)
{
	struct agp_client *client;
	struct agp_client *prev_client;
	struct agp_client *next_client;
	struct agp_controller *controller;

	controller = agp_find_controller_for_client(id);
	if (controller == NULL)
		return -EINVAL;

	client = agp_find_client_in_controller(controller, id);
	if (client == NULL)
		return -EINVAL;

	prev_client = client->prev;
	next_client = client->next;

	if (prev_client != NULL) {
		prev_client->next = next_client;
		if (next_client != NULL)
			next_client->prev = prev_client;

	} else {
		if (next_client != NULL)
			next_client->prev = NULL;
		controller->clients = next_client;
	}

	controller->num_clients--;
	agp_remove_seg_from_client(client);
	kfree(client);
	return 0;
}