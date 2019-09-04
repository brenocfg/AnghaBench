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
typedef  int LAYER_TYPE ;

/* Variables and functions */
#define  ACTIVE 150 
#define  AVGPOOL 149 
#define  BATCHNORM 148 
#define  CONNECTED 147 
#define  CONVOLUTIONAL 146 
#define  COST 145 
#define  CRNN 144 
#define  CROP 143 
#define  DECONVOLUTIONAL 142 
#define  DETECTION 141 
#define  DROPOUT 140 
#define  GRU 139 
#define  LOCAL 138 
#define  LSTM 137 
#define  MAXPOOL 136 
#define  NORMALIZATION 135 
#define  REGION 134 
#define  REORG 133 
#define  RNN 132 
#define  ROUTE 131 
#define  SHORTCUT 130 
#define  SOFTMAX 129 
#define  YOLO 128 

char *get_layer_string(LAYER_TYPE a)
{
    switch(a){
        case CONVOLUTIONAL:
            return "convolutional";
        case ACTIVE:
            return "activation";
        case LOCAL:
            return "local";
        case DECONVOLUTIONAL:
            return "deconvolutional";
        case CONNECTED:
            return "connected";
        case RNN:
            return "rnn";
        case GRU:
            return "gru";
        case LSTM:
	    return "lstm";
        case CRNN:
            return "crnn";
        case MAXPOOL:
            return "maxpool";
        case REORG:
            return "reorg";
        case AVGPOOL:
            return "avgpool";
        case SOFTMAX:
            return "softmax";
        case DETECTION:
            return "detection";
        case REGION:
            return "region";
        case YOLO:
            return "yolo";
        case DROPOUT:
            return "dropout";
        case CROP:
            return "crop";
        case COST:
            return "cost";
        case ROUTE:
            return "route";
        case SHORTCUT:
            return "shortcut";
        case NORMALIZATION:
            return "normalization";
        case BATCHNORM:
            return "batchnorm";
        default:
            break;
    }
    return "none";
}