#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  char uchar ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {size_t tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; int /*<<< orphan*/  tm_year; } ;
struct stat {int /*<<< orphan*/  st_mtime; } ;
struct line_map {char* to_file; } ;
struct _cpp_file {int dummy; } ;
struct TYPE_22__ {int /*<<< orphan*/  in_directive; } ;
struct TYPE_23__ {char* date; char* time; int /*<<< orphan*/  counter; TYPE_3__ state; TYPE_1__* cur_token; TYPE_7__* line_table; } ;
typedef  TYPE_4__ cpp_reader ;
struct TYPE_21__ {int builtin; } ;
struct TYPE_24__ {TYPE_2__ value; } ;
typedef  TYPE_5__ cpp_hashnode ;
struct TYPE_25__ {unsigned char* timestamp; } ;
typedef  TYPE_6__ cpp_buffer ;
struct TYPE_26__ {unsigned int highest_line; int /*<<< orphan*/  used; struct line_map* maps; int /*<<< orphan*/  depth; } ;
struct TYPE_20__ {unsigned int src_loc; } ;

/* Variables and functions */
#define  BT_BASE_FILE 136 
#define  BT_COUNTER 135 
#define  BT_DATE 134 
#define  BT_FILE 133 
#define  BT_INCLUDE_LEVEL 132 
#define  BT_SPECLINE 131 
#define  BT_STDC 130 
#define  BT_TIME 129 
#define  BT_TIMESTAMP 128 
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 int /*<<< orphan*/  CPP_DL_ICE ; 
 int /*<<< orphan*/  CPP_DL_WARNING ; 
 int /*<<< orphan*/  CPP_OPTION (TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct line_map* INCLUDED_FROM (TYPE_7__*,struct line_map const*) ; 
 int /*<<< orphan*/  MAIN_FILE_P (struct line_map const*) ; 
 int /*<<< orphan*/  NODE_NAME (TYPE_5__*) ; 
 unsigned int SOURCE_LINE (struct line_map const*,unsigned int) ; 
 struct stat* _cpp_get_file_stat (struct _cpp_file*) ; 
 void* _cpp_unaligned_alloc (TYPE_4__*,int) ; 
 char* asctime (struct tm*) ; 
 int /*<<< orphan*/  cpp_errno (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpp_error (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_6__* cpp_get_buffer (TYPE_4__*) ; 
 struct _cpp_file* cpp_get_file (TYPE_6__*) ; 
 int /*<<< orphan*/  cpp_in_system_header (TYPE_4__*) ; 
 char* cpp_quote_string (char*,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  directives_only ; 
 int /*<<< orphan*/  errno ; 
 struct line_map* linemap_lookup (TYPE_7__*,unsigned int) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 char** monthnames ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 void* strlen (char const*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  traditional ; 

const uchar *
_cpp_builtin_macro_text (cpp_reader *pfile, cpp_hashnode *node)
{
  const struct line_map *map;
  const uchar *result = NULL;
  unsigned int number = 1;

  switch (node->value.builtin)
    {
    default:
      cpp_error (pfile, CPP_DL_ICE, "invalid built-in macro \"%s\"",
		 NODE_NAME (node));
      break;

    case BT_TIMESTAMP:
      {
	cpp_buffer *pbuffer = cpp_get_buffer (pfile);
	if (pbuffer->timestamp == NULL)
	  {
	    /* Initialize timestamp value of the assotiated file. */
            struct _cpp_file *file = cpp_get_file (pbuffer);
	    if (file)
	      {
    		/* Generate __TIMESTAMP__ string, that represents 
		   the date and time of the last modification 
		   of the current source file. The string constant 
		   looks like "Sun Sep 16 01:03:52 1973".  */
		struct tm *tb = NULL;
		struct stat *st = _cpp_get_file_stat (file);
		if (st)
		  tb = localtime (&st->st_mtime);
		if (tb)
		  {
		    char *str = asctime (tb);
		    size_t len = strlen (str);
		    unsigned char *buf = _cpp_unaligned_alloc (pfile, len + 2);
		    buf[0] = '"';
		    strcpy ((char *) buf + 1, str);
		    buf[len] = '"';
		    pbuffer->timestamp = buf;
		  }
		else
		  {
		    cpp_errno (pfile, CPP_DL_WARNING,
			"could not determine file timestamp");
		    pbuffer->timestamp = U"\"??? ??? ?? ??:??:?? ????\"";
		  }
	      }
	  }
	result = pbuffer->timestamp;
      }
      break;
    case BT_FILE:
    case BT_BASE_FILE:
      {
	unsigned int len;
	const char *name;
	uchar *buf;
	map = linemap_lookup (pfile->line_table, pfile->line_table->highest_line);

	if (node->value.builtin == BT_BASE_FILE)
	  while (! MAIN_FILE_P (map))
	    map = INCLUDED_FROM (pfile->line_table, map);

	name = map->to_file;
	len = strlen (name);
	buf = _cpp_unaligned_alloc (pfile, len * 2 + 3);
	result = buf;
	*buf = '"';
	buf = cpp_quote_string (buf + 1, (const unsigned char *) name, len);
	*buf++ = '"';
	*buf = '\0';
      }
      break;

    case BT_INCLUDE_LEVEL:
      /* The line map depth counts the primary source as level 1, but
	 historically __INCLUDE_DEPTH__ has called the primary source
	 level 0.  */
      number = pfile->line_table->depth - 1;
      break;

    case BT_SPECLINE:
      map = &pfile->line_table->maps[pfile->line_table->used-1];
      /* If __LINE__ is embedded in a macro, it must expand to the
	 line of the macro's invocation, not its definition.
	 Otherwise things like assert() will not work properly.  */
      if (CPP_OPTION (pfile, traditional))
	number = pfile->line_table->highest_line;
      else
	number = pfile->cur_token[-1].src_loc;
      number = SOURCE_LINE (map, number);
      break;

      /* __STDC__ has the value 1 under normal circumstances.
	 However, if (a) we are in a system header, (b) the option
	 stdc_0_in_system_headers is true (set by target config), and
	 (c) we are not in strictly conforming mode, then it has the
	 value 0.  (b) and (c) are already checked in cpp_init_builtins.  */
    case BT_STDC:
      if (cpp_in_system_header (pfile))
	number = 0;
      else
	number = 1;
      break;

    case BT_DATE:
    case BT_TIME:
      if (pfile->date == NULL)
	{
	  /* Allocate __DATE__ and __TIME__ strings from permanent
	     storage.  We only do this once, and don't generate them
	     at init time, because time() and localtime() are very
	     slow on some systems.  */
	  time_t tt;
	  struct tm *tb = NULL;

	  /* (time_t) -1 is a legitimate value for "number of seconds
	     since the Epoch", so we have to do a little dance to
	     distinguish that from a genuine error.  */
	  errno = 0;
	  tt = time(NULL);
	  if (tt != (time_t)-1 || errno == 0)
	    tb = localtime (&tt);

	  if (tb)
	    {
	      pfile->date = _cpp_unaligned_alloc (pfile,
						  sizeof ("\"Oct 11 1347\""));
	      sprintf ((char *) pfile->date, "\"%s %2d %4d\"",
		       monthnames[tb->tm_mon], tb->tm_mday,
		       tb->tm_year + 1900);

	      pfile->time = _cpp_unaligned_alloc (pfile,
						  sizeof ("\"12:34:56\""));
	      sprintf ((char *) pfile->time, "\"%02d:%02d:%02d\"",
		       tb->tm_hour, tb->tm_min, tb->tm_sec);
	    }
	  else
	    {
	      cpp_errno (pfile, CPP_DL_WARNING,
			 "could not determine date and time");
		
	      pfile->date = U"\"??? ?? ????\"";
	      pfile->time = U"\"??:??:??\"";
	    }
	}

      if (node->value.builtin == BT_DATE)
	result = pfile->date;
      else
	result = pfile->time;
      break;

    case BT_COUNTER:
      if (CPP_OPTION (pfile, directives_only) && pfile->state.in_directive)
	cpp_error (pfile, CPP_DL_ERROR,
	    "__COUNTER__ expanded inside directive with -fdirectives-only");
      number = pfile->counter++;
      break;
    }

  if (result == NULL)
    {
      /* 21 bytes holds all NUL-terminated unsigned 64-bit numbers.  */
      result = _cpp_unaligned_alloc (pfile, 21);
      sprintf ((char *) result, "%u", number);
    }

  return result;      
}