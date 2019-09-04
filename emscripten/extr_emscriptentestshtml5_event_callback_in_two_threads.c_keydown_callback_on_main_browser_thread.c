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
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ EmscriptenKeyboardEvent ;
typedef  int EM_BOOL ;

/* Variables and functions */
 int DOM_PK_ENTER ; 
 int /*<<< orphan*/  assert (int) ; 
 int emscripten_compute_dom_pk_code (int /*<<< orphan*/ ) ; 
 char* emscripten_dom_pk_code_to_string (int) ; 
 int /*<<< orphan*/  keydown_callback_on_application_main_thread (int,TYPE_1__ const*,void*) ; 
 void* main_browser_thread_id ; 
 int /*<<< orphan*/  printf (char*,void*,void*,char*) ; 
 scalar_t__ pthread_self () ; 
 int saw_keydown_event_on_enter_key_on_main_browser_thread ; 

EM_BOOL keydown_callback_on_main_browser_thread(int eventType, const EmscriptenKeyboardEvent *e, void *userData)
{
  int dom_pk_code = emscripten_compute_dom_pk_code(e->code);
  printf("keydown_callback_on_main_browser_thread received on pthread: %p, main_browser_thread_id; %p, dom_pk_code: %s\n", (void*)pthread_self(), main_browser_thread_id, emscripten_dom_pk_code_to_string(dom_pk_code));
  assert((void*)pthread_self() == main_browser_thread_id);

#if __EMSCRIPTEN_PTHREADS__
  EmscriptenKeyboardEvent *duplicatedEventStruct = malloc(sizeof(*e));
  memcpy(duplicatedEventStruct, e, sizeof(*e));
  emscripten_async_queue_on_thread(application_main_thread_id, EM_FUNC_SIG_IIII, keydown_callback_on_application_main_thread, duplicatedEventStruct, eventType, duplicatedEventStruct, userData);
#else
  keydown_callback_on_application_main_thread(eventType, e, userData);
#endif

  if (dom_pk_code == DOM_PK_ENTER) saw_keydown_event_on_enter_key_on_main_browser_thread = 1;

  return dom_pk_code == DOM_PK_ENTER; // Suppress default event handling for the enter/return key so that it should not generate the keypress event.
}