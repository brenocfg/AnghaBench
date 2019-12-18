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
typedef  int /*<<< orphan*/  curl_socket_t ;
struct TYPE_4__ {int /*<<< orphan*/  poll_handle; } ;
typedef  TYPE_1__ curl_context_t ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
#define  CURL_POLL_IN 131 
#define  CURL_POLL_INOUT 130 
#define  CURL_POLL_OUT 129 
#define  CURL_POLL_REMOVE 128 
 int UV_READABLE ; 
 int UV_WRITABLE ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_1__* create_curl_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_handle ; 
 int /*<<< orphan*/  curl_multi_assign (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  curl_perform ; 
 int /*<<< orphan*/  destroy_curl_context (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_poll_start (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_poll_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_socket(CURL *easy, curl_socket_t s, int action, void *userp,
                  void *socketp)
{
  curl_context_t *curl_context;
  int events = 0;

  switch(action) {
  case CURL_POLL_IN:
  case CURL_POLL_OUT:
  case CURL_POLL_INOUT:
    curl_context = socketp ?
      (curl_context_t *) socketp : create_curl_context(s);

    curl_multi_assign(curl_handle, s, (void *) curl_context);

    if(action != CURL_POLL_IN)
      events |= UV_WRITABLE;
    if(action != CURL_POLL_OUT)
      events |= UV_READABLE;

    uv_poll_start(&curl_context->poll_handle, events, curl_perform);
    break;
  case CURL_POLL_REMOVE:
    if(socketp) {
      uv_poll_stop(&((curl_context_t*)socketp)->poll_handle);
      destroy_curl_context((curl_context_t*) socketp);
      curl_multi_assign(curl_handle, s, NULL);
    }
    break;
  default:
    abort();
  }

  return 0;
}