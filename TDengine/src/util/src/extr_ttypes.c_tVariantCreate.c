#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tVariant ;
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  n; int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ SSQLToken ;

/* Variables and functions */
 int /*<<< orphan*/  tVariantCreateFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tVariantCreate(tVariant *pVar, SSQLToken *token) { tVariantCreateFromString(pVar, token->z, token->n, token->type); }