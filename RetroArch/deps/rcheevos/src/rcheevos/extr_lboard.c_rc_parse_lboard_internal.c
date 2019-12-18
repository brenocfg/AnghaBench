#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ offset; } ;
typedef  TYPE_1__ rc_parse_state_t ;
struct TYPE_13__ {scalar_t__ memrefs; } ;
struct TYPE_14__ {scalar_t__ memrefs; } ;
struct TYPE_12__ {scalar_t__ submitted; scalar_t__ started; TYPE_3__* progress; TYPE_3__ value; TYPE_5__ submit; TYPE_5__ cancel; TYPE_5__ start; } ;
typedef  TYPE_2__ rc_lboard_t ;

/* Variables and functions */
 TYPE_3__* RC_ALLOC (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ RC_DUPLICATED_CANCEL ; 
 scalar_t__ RC_DUPLICATED_PROGRESS ; 
 scalar_t__ RC_DUPLICATED_START ; 
 scalar_t__ RC_DUPLICATED_SUBMIT ; 
 scalar_t__ RC_DUPLICATED_VALUE ; 
 scalar_t__ RC_INVALID_LBOARD_FIELD ; 
 int RC_LBOARD_CANCEL ; 
 int RC_LBOARD_COMPLETE ; 
 int RC_LBOARD_PROGRESS ; 
 int RC_LBOARD_START ; 
 int RC_LBOARD_SUBMIT ; 
 int RC_LBOARD_VALUE ; 
 scalar_t__ RC_MISSING_CANCEL ; 
 scalar_t__ RC_MISSING_START ; 
 scalar_t__ RC_MISSING_SUBMIT ; 
 scalar_t__ RC_MISSING_VALUE ; 
 int /*<<< orphan*/  rc_parse_trigger_internal (TYPE_5__*,char const**,TYPE_1__*) ; 
 int /*<<< orphan*/  rc_parse_value_internal (TYPE_3__*,char const**,TYPE_1__*) ; 
 int /*<<< orphan*/  rc_value_t ; 

void rc_parse_lboard_internal(rc_lboard_t* self, const char* memaddr, rc_parse_state_t* parse) {
  int found;

  self->progress = 0;
  found = 0;

  for (;;)
  {
    if ((memaddr[0] == 's' || memaddr[0] == 'S') &&
        (memaddr[1] == 't' || memaddr[1] == 'T') &&
        (memaddr[2] == 'a' || memaddr[2] == 'A') && memaddr[3] == ':') {
      if ((found & RC_LBOARD_START) != 0) {
        parse->offset = RC_DUPLICATED_START;
        return;
      }

      found |= RC_LBOARD_START;
      memaddr += 4;
      rc_parse_trigger_internal(&self->start, &memaddr, parse);
      self->start.memrefs = 0;

      if (parse->offset < 0) {
        return;
      }
    }
    else if ((memaddr[0] == 'c' || memaddr[0] == 'C') &&
             (memaddr[1] == 'a' || memaddr[1] == 'A') &&
             (memaddr[2] == 'n' || memaddr[2] == 'N') && memaddr[3] == ':') {
      if ((found & RC_LBOARD_CANCEL) != 0) {
        parse->offset = RC_DUPLICATED_CANCEL;
        return;
      }

      found |= RC_LBOARD_CANCEL;
      memaddr += 4;
      rc_parse_trigger_internal(&self->cancel, &memaddr, parse);
      self->cancel.memrefs = 0;

      if (parse->offset < 0) {
        return;
      }
    }
    else if ((memaddr[0] == 's' || memaddr[0] == 'S') &&
             (memaddr[1] == 'u' || memaddr[1] == 'U') &&
             (memaddr[2] == 'b' || memaddr[2] == 'B') && memaddr[3] == ':') {
      if ((found & RC_LBOARD_SUBMIT) != 0) {
        parse->offset = RC_DUPLICATED_SUBMIT;
        return;
      }

      found |= RC_LBOARD_SUBMIT;
      memaddr += 4;
      rc_parse_trigger_internal(&self->submit, &memaddr, parse);
      self->submit.memrefs = 0;

      if (parse->offset < 0) {
        return;
      }
    }
    else if ((memaddr[0] == 'v' || memaddr[0] == 'V') &&
             (memaddr[1] == 'a' || memaddr[1] == 'A') &&
             (memaddr[2] == 'l' || memaddr[2] == 'L') && memaddr[3] == ':') {
      if ((found & RC_LBOARD_VALUE) != 0) {
        parse->offset = RC_DUPLICATED_VALUE;
        return;
      }

      found |= RC_LBOARD_VALUE;
      memaddr += 4;
      rc_parse_value_internal(&self->value, &memaddr, parse);
      self->value.memrefs = 0;

      if (parse->offset < 0) {
        return;
      }
    }
    else if ((memaddr[0] == 'p' || memaddr[0] == 'P') &&
             (memaddr[1] == 'r' || memaddr[1] == 'R') &&
             (memaddr[2] == 'o' || memaddr[2] == 'O') && memaddr[3] == ':') {
      if ((found & RC_LBOARD_PROGRESS) != 0) {
        parse->offset = RC_DUPLICATED_PROGRESS;
        return;
      }

      found |= RC_LBOARD_PROGRESS;
      memaddr += 4;

      self->progress = RC_ALLOC(rc_value_t, parse);
      rc_parse_value_internal(self->progress, &memaddr, parse);
      self->progress->memrefs = 0;

      if (parse->offset < 0) {
        return;
      }
    }
    else {
      parse->offset = RC_INVALID_LBOARD_FIELD;
      return;
    }

    if (memaddr[0] != ':' || memaddr[1] != ':') {
      break;
    }

    memaddr += 2;
  }

  if ((found & RC_LBOARD_COMPLETE) != RC_LBOARD_COMPLETE) {
    if ((found & RC_LBOARD_START) == 0) {
      parse->offset = RC_MISSING_START;
    }
    else if ((found & RC_LBOARD_CANCEL) == 0) {
      parse->offset = RC_MISSING_CANCEL;
    }
    else if ((found & RC_LBOARD_SUBMIT) == 0) {
      parse->offset = RC_MISSING_SUBMIT;
    }
    else if ((found & RC_LBOARD_VALUE) == 0) {
      parse->offset = RC_MISSING_VALUE;
    }

    return;
  }

  self->started = self->submitted = 0;
}