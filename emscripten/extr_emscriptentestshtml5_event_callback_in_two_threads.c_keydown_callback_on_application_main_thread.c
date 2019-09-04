#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ EmscriptenKeyboardEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int DOM_PK_ENTER ; 
 void* application_main_thread_id ; 
 int /*<<< orphan*/  assert (int) ; 
 int emscripten_compute_dom_pk_code (int /*<<< orphan*/ ) ; 
 char* emscripten_dom_pk_code_to_string (int) ; 
 int /*<<< orphan*/  printf (char*,void*,void*,char*) ; 
 scalar_t__ pthread_self () ; 
 int saw_keydown_event_on_enter_key_on_application_main_thread ; 

EM_BOOL keydown_callback_on_application_main_thread(int eventType, const EmscriptenKeyboardEvent *e, void *userData)
{
  int dom_pk_code = emscripten_compute_dom_pk_code(e->code);
  printf("keydown_callback_on_application_main_thread received on pthread: %p, application_main_thread_id: %p, dom_pk_code: %s\n", (void*)pthread_self(), application_main_thread_id, emscripten_dom_pk_code_to_string(dom_pk_code));
  assert((void*)pthread_self() == application_main_thread_id);

  if (dom_pk_code == DOM_PK_ENTER) saw_keydown_event_on_enter_key_on_application_main_thread = 1;
  return 0;
}