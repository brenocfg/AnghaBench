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

/* Variables and functions */
#define  PhysConn_Audio_1394 150 
#define  PhysConn_Audio_AESDigital 149 
#define  PhysConn_Audio_AUX 148 
#define  PhysConn_Audio_AudioDecoder 147 
#define  PhysConn_Audio_Line 146 
#define  PhysConn_Audio_Mic 145 
#define  PhysConn_Audio_SCSI 144 
#define  PhysConn_Audio_SPDIFDigital 143 
#define  PhysConn_Audio_Tuner 142 
#define  PhysConn_Audio_USB 141 
#define  PhysConn_Video_1394 140 
#define  PhysConn_Video_AUX 139 
#define  PhysConn_Video_Composite 138 
#define  PhysConn_Video_ParallelDigital 137 
#define  PhysConn_Video_RGB 136 
#define  PhysConn_Video_SCSI 135 
#define  PhysConn_Video_SVideo 134 
#define  PhysConn_Video_SerialDigital 133 
#define  PhysConn_Video_Tuner 132 
#define  PhysConn_Video_USB 131 
#define  PhysConn_Video_VideoDecoder 130 
#define  PhysConn_Video_VideoEncoder 129 
#define  PhysConn_Video_YRYBY 128 

__attribute__((used)) static const char *
GetPhysicalPinName(long pin_type)
{
    switch (pin_type)
    {
    case PhysConn_Video_Tuner:            return "Video Tuner";
    case PhysConn_Video_Composite:        return "Video Composite";
    case PhysConn_Video_SVideo:           return "S-Video";
    case PhysConn_Video_RGB:              return "Video RGB";
    case PhysConn_Video_YRYBY:            return "Video YRYBY";
    case PhysConn_Video_SerialDigital:    return "Video Serial Digital";
    case PhysConn_Video_ParallelDigital:  return "Video Parallel Digital";
    case PhysConn_Video_SCSI:             return "Video SCSI";
    case PhysConn_Video_AUX:              return "Video AUX";
    case PhysConn_Video_1394:             return "Video 1394";
    case PhysConn_Video_USB:              return "Video USB";
    case PhysConn_Video_VideoDecoder:     return "Video Decoder";
    case PhysConn_Video_VideoEncoder:     return "Video Encoder";

    case PhysConn_Audio_Tuner:            return "Audio Tuner";
    case PhysConn_Audio_Line:             return "Audio Line";
    case PhysConn_Audio_Mic:              return "Audio Microphone";
    case PhysConn_Audio_AESDigital:       return "Audio AES/EBU Digital";
    case PhysConn_Audio_SPDIFDigital:     return "Audio S/PDIF";
    case PhysConn_Audio_SCSI:             return "Audio SCSI";
    case PhysConn_Audio_AUX:              return "Audio AUX";
    case PhysConn_Audio_1394:             return "Audio 1394";
    case PhysConn_Audio_USB:              return "Audio USB";
    case PhysConn_Audio_AudioDecoder:     return "Audio Decoder";
    default:                              return "Unknown Crossbar Pin Type—Please report!";
    }
}