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
struct TYPE_2__ {int /*<<< orphan*/  sockfd; } ;
typedef  TYPE_1__ curl_context_t ;

/* Variables and functions */
 int CURL_CSELECT_IN ; 
 int CURL_CSELECT_OUT ; 
 short EV_READ ; 
 short EV_WRITE ; 
 int /*<<< orphan*/  check_multi_info () ; 
 int /*<<< orphan*/  curl_handle ; 
 int /*<<< orphan*/  curl_multi_socket_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void curl_perform(int fd, short event, void *arg)
{
  int running_handles;
  int flags = 0;
  curl_context_t *context;

  if(event & EV_READ)
    flags |= CURL_CSELECT_IN;
  if(event & EV_WRITE)
    flags |= CURL_CSELECT_OUT;

  context = (curl_context_t *) arg;

  curl_multi_socket_action(curl_handle, context->sockfd, flags,
                           &running_handles);

  check_multi_info();
}