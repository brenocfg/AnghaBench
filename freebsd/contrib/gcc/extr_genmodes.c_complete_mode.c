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
struct mode_data {char* line; int cl; int precision; int bytesize; int ncomponents; unsigned int alignment; TYPE_1__* component; struct mode_data* next_cont; int /*<<< orphan*/  name; int /*<<< orphan*/  file; } ;
struct TYPE_2__ {int bytesize; unsigned int precision; struct mode_data* contained; } ;

/* Variables and functions */
 int MAX_MODE_CLASS ; 
#define  MODE_CC 137 
#define  MODE_COMPLEX_FLOAT 136 
#define  MODE_COMPLEX_INT 135 
#define  MODE_DECIMAL_FLOAT 134 
#define  MODE_FLOAT 133 
#define  MODE_INT 132 
#define  MODE_PARTIAL_INT 131 
#define  MODE_RANDOM 130 
#define  MODE_VECTOR_FLOAT 129 
#define  MODE_VECTOR_INT 128 
 int /*<<< orphan*/  OPTIONAL ; 
 int /*<<< orphan*/  SET ; 
 int /*<<< orphan*/  UNSET ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  validate_mode (struct mode_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mode_data* void_mode ; 

__attribute__((used)) static void
complete_mode (struct mode_data *m)
{
  unsigned int alignment;

  if (!m->name)
    {
      error ("%s:%d: mode with no name", m->file, m->line);
      return;
    }
  if (m->cl == MAX_MODE_CLASS)
    {
      error ("%s:%d: %smode has no mode class", m->file, m->line, m->name);
      return;
    }

  switch (m->cl)
    {
    case MODE_RANDOM:
      /* Nothing more need be said.  */
      if (!strcmp (m->name, "VOID"))
	void_mode = m;

      validate_mode (m, UNSET, UNSET, UNSET, UNSET, UNSET);

      m->precision = 0;
      m->bytesize = 0;
      m->ncomponents = 0;
      m->component = 0;
      break;

    case MODE_CC:
      /* Again, nothing more need be said.  For historical reasons,
	 the size of a CC mode is four units.  */
      validate_mode (m, UNSET, UNSET, UNSET, UNSET, UNSET);

      m->bytesize = 4;
      m->ncomponents = 1;
      m->component = 0;
      break;

    case MODE_INT:
    case MODE_FLOAT:
    case MODE_DECIMAL_FLOAT:
      /* A scalar mode must have a byte size, may have a bit size,
	 and must not have components.   A float mode must have a
         format.  */
      validate_mode (m, OPTIONAL, SET, UNSET, UNSET,
		     m->cl != MODE_INT ? SET : UNSET);

      m->ncomponents = 1;
      m->component = 0;
      break;

    case MODE_PARTIAL_INT:
      /* A partial integer mode uses ->component to say what the
	 corresponding full-size integer mode is, and may also
	 specify a bit size.  */
      validate_mode (m, OPTIONAL, UNSET, SET, UNSET, UNSET);

      m->bytesize = m->component->bytesize;

      m->ncomponents = 1;
      m->component = 0;  /* ??? preserve this */
      break;

    case MODE_COMPLEX_INT:
    case MODE_COMPLEX_FLOAT:
      /* Complex modes should have a component indicated, but no more.  */
      validate_mode (m, UNSET, UNSET, SET, UNSET, UNSET);
      m->ncomponents = 2;
      if (m->component->precision != (unsigned int)-1)
	m->precision = 2 * m->component->precision;
      m->bytesize = 2 * m->component->bytesize;
      break;

    case MODE_VECTOR_INT:
    case MODE_VECTOR_FLOAT:
      /* Vector modes should have a component and a number of components.  */
      validate_mode (m, UNSET, UNSET, SET, SET, UNSET);
      if (m->component->precision != (unsigned int)-1)
	m->precision = m->ncomponents * m->component->precision;
      m->bytesize = m->ncomponents * m->component->bytesize;
      break;

    default:
      gcc_unreachable ();
    }

  /* If not already specified, the mode alignment defaults to the largest
     power of two that divides the size of the object.  Complex types are
     not more aligned than their contents.  */
  if (m->cl == MODE_COMPLEX_INT || m->cl == MODE_COMPLEX_FLOAT)
    alignment = m->component->bytesize;
  else
    alignment = m->bytesize;

  m->alignment = alignment & (~alignment + 1);

  /* If this mode has components, make the component mode point back
     to this mode, for the sake of adjustments.  */
  if (m->component)
    {
      m->next_cont = m->component->contained;
      m->component->contained = m;
    }
}