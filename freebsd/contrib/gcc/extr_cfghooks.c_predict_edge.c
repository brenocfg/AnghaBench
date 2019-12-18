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
typedef  enum br_predictor { ____Placeholder_br_predictor } br_predictor ;
typedef  int /*<<< orphan*/  edge ;
struct TYPE_2__ {int /*<<< orphan*/  (* predict_edge ) (int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* cfg_hooks ; 
 int /*<<< orphan*/  internal_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 

void
predict_edge (edge e, enum br_predictor predictor, int probability)
{
  if (!cfg_hooks->predict_edge)
    internal_error ("%s does not support predict_edge", cfg_hooks->name);

  cfg_hooks->predict_edge (e, predictor, probability);
}