#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int max_score; struct TYPE_7__* next; } ;
struct TYPE_6__ {TYPE_2__* best_header; TYPE_2__* headers; } ;
typedef  TYPE_1__ FLACParseContext ;
typedef  TYPE_2__ FLACHeaderMarker ;

/* Variables and functions */
 int FLAC_HEADER_NOT_SCORED_YET ; 
 int score_header (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void score_sequences(FLACParseContext *fpc)
{
    FLACHeaderMarker *curr;
    int best_score = 0;//FLAC_HEADER_NOT_SCORED_YET;
    /* First pass to clear all old scores. */
    for (curr = fpc->headers; curr; curr = curr->next)
        curr->max_score = FLAC_HEADER_NOT_SCORED_YET;

    /* Do a second pass to score them all. */
    for (curr = fpc->headers; curr; curr = curr->next) {
        if (score_header(fpc, curr) > best_score) {
            fpc->best_header = curr;
            best_score       = curr->max_score;
        }
    }
}