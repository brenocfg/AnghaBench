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
typedef  int /*<<< orphan*/  DWTELEM ;

/* Variables and functions */
 int /*<<< orphan*/  W_AM ; 
 int /*<<< orphan*/  W_AO ; 
 int /*<<< orphan*/  W_AS ; 
 int /*<<< orphan*/  W_BM ; 
 int /*<<< orphan*/  W_BO ; 
 int /*<<< orphan*/  W_BS ; 
 int /*<<< orphan*/  W_CM ; 
 int /*<<< orphan*/  W_CO ; 
 int /*<<< orphan*/  W_CS ; 
 int /*<<< orphan*/  W_DM ; 
 int /*<<< orphan*/  W_DO ; 
 int /*<<< orphan*/  W_DS ; 
 int /*<<< orphan*/  lift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  liftS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void horizontal_decompose97i(DWTELEM *b, DWTELEM *temp, int width)
{
    const int w2 = (width + 1) >> 1;

    lift(temp + w2, b + 1, b,         1, 2, 2, width, W_AM, W_AO, W_AS, 1, 1);
    liftS(temp,     b,     temp + w2, 1, 2, 1, width, W_BM, W_BO, W_BS, 0, 0);
    lift(b + w2, temp + w2, temp,     1, 1, 1, width, W_CM, W_CO, W_CS, 1, 0);
    lift(b,      temp,      b + w2,   1, 1, 1, width, W_DM, W_DO, W_DS, 0, 0);
}