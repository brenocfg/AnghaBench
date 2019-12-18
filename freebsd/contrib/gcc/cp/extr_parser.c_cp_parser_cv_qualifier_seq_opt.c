#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int keyword; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_6__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;
typedef  int cp_cv_quals ;

/* Variables and functions */
#define  RID_CONST 130 
#define  RID_RESTRICT 129 
#define  RID_VOLATILE 128 
 int TYPE_QUAL_CONST ; 
 int TYPE_QUAL_RESTRICT ; 
 int TYPE_QUAL_VOLATILE ; 
 int TYPE_UNQUALIFIED ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_purge_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static cp_cv_quals
cp_parser_cv_qualifier_seq_opt (cp_parser* parser)
{
  cp_cv_quals cv_quals = TYPE_UNQUALIFIED;

  while (true)
    {
      cp_token *token;
      cp_cv_quals cv_qualifier;

      /* Peek at the next token.  */
      token = cp_lexer_peek_token (parser->lexer);
      /* See if it's a cv-qualifier.  */
      switch (token->keyword)
	{
	case RID_CONST:
	  cv_qualifier = TYPE_QUAL_CONST;
	  break;

	case RID_VOLATILE:
	  cv_qualifier = TYPE_QUAL_VOLATILE;
	  break;

	case RID_RESTRICT:
	  cv_qualifier = TYPE_QUAL_RESTRICT;
	  break;

	default:
	  cv_qualifier = TYPE_UNQUALIFIED;
	  break;
	}

      if (!cv_qualifier)
	break;

      if (cv_quals & cv_qualifier)
	{
	  error ("duplicate cv-qualifier");
	  cp_lexer_purge_token (parser->lexer);
	}
      else
	{
	  cp_lexer_consume_token (parser->lexer);
	  cv_quals |= cv_qualifier;
	}
    }

  return cv_quals;
}