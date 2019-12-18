#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ type_kind_t ;
struct work_stuff {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  b; } ;
typedef  TYPE_1__ string ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_BLANK (TYPE_1__*) ; 
 int /*<<< orphan*/  INTBUF_SIZE ; 
 int /*<<< orphan*/  ISDIGIT (unsigned char) ; 
 int /*<<< orphan*/  LEN_STRING (TYPE_1__*) ; 
 int /*<<< orphan*/  PRINT_ANSI_QUALIFIERS ; 
 int /*<<< orphan*/  STRING_EMPTY (TYPE_1__*) ; 
 int /*<<< orphan*/  demangle_class_name (struct work_stuff*,char const**,TYPE_1__*) ; 
 char* demangle_qualifier (char const) ; 
 int demangle_template (struct work_stuff*,char const**,TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int register_Btype (struct work_stuff*) ; 
 int /*<<< orphan*/  remember_Btype (struct work_stuff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,unsigned int*) ; 
 int /*<<< orphan*/  string_append (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  string_appends (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  string_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  string_init (TYPE_1__*) ; 
 int /*<<< orphan*/  string_prepend (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 scalar_t__ tk_bool ; 
 scalar_t__ tk_char ; 
 scalar_t__ tk_integral ; 
 scalar_t__ tk_real ; 

__attribute__((used)) static int
demangle_fund_type (struct work_stuff *work,
                    const char **mangled, string *result)
{
  int done = 0;
  int success = 1;
  char buf[INTBUF_SIZE + 5 /* 'int%u_t' */];
  unsigned int dec = 0;
  type_kind_t tk = tk_integral;

  /* First pick off any type qualifiers.  There can be more than one.  */

  while (!done)
    {
      switch (**mangled)
	{
	case 'C':
	case 'V':
	case 'u':
	  if (PRINT_ANSI_QUALIFIERS)
	    {
              if (!STRING_EMPTY (result))
                string_prepend (result, " ");
	      string_prepend (result, demangle_qualifier (**mangled));
	    }
	  (*mangled)++;
	  break;
	case 'U':
	  (*mangled)++;
	  APPEND_BLANK (result);
	  string_append (result, "unsigned");
	  break;
	case 'S': /* signed char only */
	  (*mangled)++;
	  APPEND_BLANK (result);
	  string_append (result, "signed");
	  break;
	case 'J':
	  (*mangled)++;
	  APPEND_BLANK (result);
	  string_append (result, "__complex");
	  break;
	default:
	  done = 1;
	  break;
	}
    }

  /* Now pick off the fundamental type.  There can be only one.  */

  switch (**mangled)
    {
    case '\0':
    case '_':
      break;
    case 'v':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "void");
      break;
    case 'x':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "long long");
      break;
    case 'l':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "long");
      break;
    case 'i':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "int");
      break;
    case 's':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "short");
      break;
    case 'b':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "bool");
      tk = tk_bool;
      break;
    case 'c':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "char");
      tk = tk_char;
      break;
    case 'w':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "wchar_t");
      tk = tk_char;
      break;
    case 'r':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "long double");
      tk = tk_real;
      break;
    case 'd':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "double");
      tk = tk_real;
      break;
    case 'f':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "float");
      tk = tk_real;
      break;
    case 'G':
      (*mangled)++;
      if (!ISDIGIT ((unsigned char)**mangled))
	{
	  success = 0;
	  break;
	}
    case 'I':
      (*mangled)++;
      if (**mangled == '_')
	{
	  int i;
	  (*mangled)++;
	  for (i = 0;
	       i < (long) sizeof (buf) - 1 && **mangled && **mangled != '_';
	       (*mangled)++, i++)
	    buf[i] = **mangled;
	  if (**mangled != '_')
	    {
	      success = 0;
	      break;
	    }
	  buf[i] = '\0';
	  (*mangled)++;
	}
      else
	{
	  strncpy (buf, *mangled, 2);
	  buf[2] = '\0';
	  *mangled += min (strlen (*mangled), 2);
	}
      sscanf (buf, "%x", &dec);
      sprintf (buf, "int%u_t", dec);
      APPEND_BLANK (result);
      string_append (result, buf);
      break;

      /* fall through */
      /* An explicit type, such as "6mytype" or "7integer" */
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      {
        int bindex = register_Btype (work);
        string btype;
        string_init (&btype);
        if (demangle_class_name (work, mangled, &btype)) {
          remember_Btype (work, btype.b, LEN_STRING (&btype), bindex);
          APPEND_BLANK (result);
          string_appends (result, &btype);
        }
        else
          success = 0;
        string_delete (&btype);
        break;
      }
    case 't':
      {
        string btype;
        string_init (&btype);
        success = demangle_template (work, mangled, &btype, 0, 1, 1);
        string_appends (result, &btype);
        string_delete (&btype);
        break;
      }
    default:
      success = 0;
      break;
    }

  return success ? ((int) tk) : 0;
}