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
typedef  int /*<<< orphan*/  TRexChar ;
typedef  int /*<<< orphan*/  TRexBool ;
typedef  int /*<<< orphan*/  TRex ;

/* Variables and functions */
 int scstrlen (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  trex_searchrange (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 

TRexBool trex_search(TRex* exp,const TRexChar* text, const TRexChar** out_begin, const TRexChar** out_end)
{
	return trex_searchrange(exp,text,text + scstrlen(text),out_begin,out_end);
}