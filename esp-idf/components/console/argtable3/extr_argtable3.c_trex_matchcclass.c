#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int TRexChar ;
typedef  int /*<<< orphan*/  TRexBool ;

/* Variables and functions */
 int /*<<< orphan*/  TRex_False ; 
 int /*<<< orphan*/  TRex_True ; 
 int /*<<< orphan*/  isalnum (int) ; 
 int /*<<< orphan*/  isalpha (int) ; 
 int /*<<< orphan*/  iscntrl (int) ; 
 int /*<<< orphan*/  isdigit (int) ; 
 int /*<<< orphan*/  islower (int) ; 
 int /*<<< orphan*/  ispunct (int) ; 
 int /*<<< orphan*/  isspace (int) ; 
 int /*<<< orphan*/  isupper (int) ; 
 int /*<<< orphan*/  isxdigit (int) ; 

__attribute__((used)) static TRexBool trex_matchcclass(int cclass,TRexChar ch)
{
    int c = ch;
	switch(cclass) {
	case 'a': return isalpha(c)?TRex_True:TRex_False;
	case 'A': return !isalpha(c)?TRex_True:TRex_False;
	case 'w': return (isalnum(c) || c == '_')?TRex_True:TRex_False;
	case 'W': return (!isalnum(c) && c != '_')?TRex_True:TRex_False;
	case 's': return isspace(c)?TRex_True:TRex_False;
	case 'S': return !isspace(c)?TRex_True:TRex_False;
	case 'd': return isdigit(c)?TRex_True:TRex_False;
	case 'D': return !isdigit(c)?TRex_True:TRex_False;
	case 'x': return isxdigit(c)?TRex_True:TRex_False;
	case 'X': return !isxdigit(c)?TRex_True:TRex_False;
	case 'c': return iscntrl(c)?TRex_True:TRex_False;
	case 'C': return !iscntrl(c)?TRex_True:TRex_False;
	case 'p': return ispunct(c)?TRex_True:TRex_False;
	case 'P': return !ispunct(c)?TRex_True:TRex_False;
	case 'l': return islower(c)?TRex_True:TRex_False;
	case 'u': return isupper(c)?TRex_True:TRex_False;
	}
	return TRex_False; /*cannot happen*/
}