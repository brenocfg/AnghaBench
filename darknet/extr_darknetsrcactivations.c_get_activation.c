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
typedef  int /*<<< orphan*/  ACTIVATION ;

/* Variables and functions */
 int /*<<< orphan*/  ELU ; 
 int /*<<< orphan*/  HARDTAN ; 
 int /*<<< orphan*/  LEAKY ; 
 int /*<<< orphan*/  LHTAN ; 
 int /*<<< orphan*/  LINEAR ; 
 int /*<<< orphan*/  LOGGY ; 
 int /*<<< orphan*/  LOGISTIC ; 
 int /*<<< orphan*/  PLSE ; 
 int /*<<< orphan*/  RAMP ; 
 int /*<<< orphan*/  RELIE ; 
 int /*<<< orphan*/  RELU ; 
 int /*<<< orphan*/  SELU ; 
 int /*<<< orphan*/  STAIR ; 
 int /*<<< orphan*/  TANH ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

ACTIVATION get_activation(char *s)
{
    if (strcmp(s, "logistic")==0) return LOGISTIC;
    if (strcmp(s, "loggy")==0) return LOGGY;
    if (strcmp(s, "relu")==0) return RELU;
    if (strcmp(s, "elu")==0) return ELU;
    if (strcmp(s, "selu")==0) return SELU;
    if (strcmp(s, "relie")==0) return RELIE;
    if (strcmp(s, "plse")==0) return PLSE;
    if (strcmp(s, "hardtan")==0) return HARDTAN;
    if (strcmp(s, "lhtan")==0) return LHTAN;
    if (strcmp(s, "linear")==0) return LINEAR;
    if (strcmp(s, "ramp")==0) return RAMP;
    if (strcmp(s, "leaky")==0) return LEAKY;
    if (strcmp(s, "tanh")==0) return TANH;
    if (strcmp(s, "stair")==0) return STAIR;
    fprintf(stderr, "Couldn't find activation function %s, going with ReLU\n", s);
    return RELU;
}