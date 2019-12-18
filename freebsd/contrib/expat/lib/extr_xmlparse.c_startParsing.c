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
typedef  TYPE_1__* XML_Parser ;
typedef  int /*<<< orphan*/  XML_Bool ;
struct TYPE_5__ {scalar_t__ m_hash_secret_salt; scalar_t__ m_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_TRUE ; 
 scalar_t__ generate_hash_secret_salt (TYPE_1__*) ; 
 int /*<<< orphan*/  implicitContext ; 
 int /*<<< orphan*/  setContext (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static XML_Bool  /* only valid for root parser */
startParsing(XML_Parser parser)
{
    /* hash functions must be initialized before setContext() is called */
    if (parser->m_hash_secret_salt == 0)
      parser->m_hash_secret_salt = generate_hash_secret_salt(parser);
    if (parser->m_ns) {
      /* implicit context only set for root parser, since child
         parsers (i.e. external entity parsers) will inherit it
      */
      return setContext(parser, implicitContext);
    }
    return XML_TRUE;
}