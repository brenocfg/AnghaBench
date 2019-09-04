#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* code; char* key; scalar_t__ keyCode; scalar_t__ altKey; scalar_t__ ctrlKey; int /*<<< orphan*/  which; int /*<<< orphan*/  charCode; int /*<<< orphan*/  charValue; int /*<<< orphan*/  locale; int /*<<< orphan*/  repeat; scalar_t__ metaKey; scalar_t__ shiftKey; int /*<<< orphan*/  location; } ;
typedef  TYPE_1__ EmscriptenKeyboardEvent ;
typedef  int EM_BOOL ;

/* Variables and functions */
 scalar_t__ DOM_VK_BACK_SPACE ; 
 scalar_t__ DOM_VK_F1 ; 
 scalar_t__ DOM_VK_F24 ; 
 scalar_t__ DOM_VK_TAB ; 
 int EMSCRIPTEN_EVENT_KEYPRESS ; 
 int EMSCRIPTEN_EVENT_KEYUP ; 
 int emscripten_compute_dom_pk_code (char*) ; 
 char* emscripten_dom_pk_code_to_string (int) ; 
 int /*<<< orphan*/  emscripten_dom_vk_to_string (scalar_t__) ; 
 char* emscripten_event_type_to_string (int) ; 
 scalar_t__ emscripten_key_event_is_printable_character (TYPE_1__ const*) ; 
 int /*<<< orphan*/  interpret_charcode_for_keyevent (int,TYPE_1__ const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

EM_BOOL key_callback(int eventType, const EmscriptenKeyboardEvent *e, void *userData)
{
  int dom_pk_code = emscripten_compute_dom_pk_code(e->code);

  printf("%s, key: \"%s\" (printable: %s), code: \"%s\" = %s (%d), location: %lu,%s%s%s%s repeat: %d, locale: \"%s\", char: \"%s\", charCode: %lu (interpreted: %d), keyCode: %s(%lu), which: %lu\n",
    emscripten_event_type_to_string(eventType), e->key, emscripten_key_event_is_printable_character(e) ? "true" : "false", e->code,
    emscripten_dom_pk_code_to_string(dom_pk_code), dom_pk_code, e->location,
    e->ctrlKey ? " CTRL" : "", e->shiftKey ? " SHIFT" : "", e->altKey ? " ALT" : "", e->metaKey ? " META" : "", 
    e->repeat, e->locale, e->charValue, e->charCode, interpret_charcode_for_keyevent(eventType, e), emscripten_dom_vk_to_string(e->keyCode), e->keyCode, e->which);

  if (eventType == EMSCRIPTEN_EVENT_KEYUP) printf("\n"); // Visual cue

  // Return true for events we want to suppress default web browser handling for.
  // For testing purposes, want to return false here on most KeyDown messages so that they get transformed to KeyPress messages.
  return e->keyCode == DOM_VK_BACK_SPACE // Don't navigate away from this test page on backspace.
    || e->keyCode == DOM_VK_TAB // Don't change keyboard focus to different browser UI elements while testing.
    || (e->keyCode >= DOM_VK_F1 && e->keyCode <= DOM_VK_F24) // Don't F5 refresh the test page to reload.
    || e->ctrlKey // Don't trigger e.g. Ctrl-B to open bookmarks
    || e->altKey // Don't trigger any alt-X based shortcuts either (Alt-F4 is not overrideable though)
    || eventType == EMSCRIPTEN_EVENT_KEYPRESS || eventType == EMSCRIPTEN_EVENT_KEYUP; // Don't perform any default actions on these.
}