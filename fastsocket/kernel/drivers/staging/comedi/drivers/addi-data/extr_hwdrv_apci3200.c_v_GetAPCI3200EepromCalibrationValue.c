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
struct str_BoardInfos {TYPE_1__* s_Module; } ;
struct TYPE_2__ {unsigned short* w_GainValue; unsigned short* ul_GainFactor; unsigned short* ul_CurrentSource; unsigned short ul_CurrentSourceCJC; } ;

/* Variables and functions */
 int /*<<< orphan*/  i_AddiHeaderRW_ReadEeprom (int,unsigned int,unsigned short,unsigned short*) ; 
 int /*<<< orphan*/  printk (char*,unsigned short,...) ; 

void v_GetAPCI3200EepromCalibrationValue(unsigned int dw_PCIBoardEepromAddress,
	struct str_BoardInfos *BoardInformations)
{
	unsigned short w_AnalogInputMainHeaderAddress;
	unsigned short w_AnalogInputComponentAddress;
	unsigned short w_NumberOfModuls = 0;
	unsigned short w_CurrentSources[2];
	unsigned short w_ModulCounter = 0;
	unsigned short w_FirstHeaderSize = 0;
	unsigned short w_NumberOfInputs = 0;
	unsigned short w_CJCFlag = 0;
	unsigned short w_NumberOfGainValue = 0;
	unsigned short w_SingleHeaderAddress = 0;
	unsigned short w_SingleHeaderSize = 0;
	unsigned short w_Input = 0;
	unsigned short w_GainFactorAddress = 0;
	unsigned short w_GainFactorValue[2];
	unsigned short w_GainIndex = 0;
	unsigned short w_GainValue = 0;

  /*****************************************/
  /** Get the Analog input header address **/
  /*****************************************/
	i_AddiHeaderRW_ReadEeprom(1,	/* i_NbOfWordsToRead */
		dw_PCIBoardEepromAddress, 0x116,	/* w_EepromStartAddress: Analog input header address */
		&w_AnalogInputMainHeaderAddress);

  /*******************************************/
  /** Compute the real analog input address **/
  /*******************************************/
	w_AnalogInputMainHeaderAddress = w_AnalogInputMainHeaderAddress + 0x100;

  /******************************/
  /** Get the number of moduls **/
  /******************************/
	i_AddiHeaderRW_ReadEeprom(1,	/* i_NbOfWordsToRead */
		dw_PCIBoardEepromAddress, w_AnalogInputMainHeaderAddress + 0x02,	/* w_EepromStartAddress: Number of conponment */
		&w_NumberOfModuls);

	for (w_ModulCounter = 0; w_ModulCounter < w_NumberOfModuls;
		w_ModulCounter++) {
      /***********************************/
      /** Compute the component address **/
      /***********************************/
		w_AnalogInputComponentAddress =
			w_AnalogInputMainHeaderAddress +
			(w_FirstHeaderSize * w_ModulCounter) + 0x04;

      /****************************/
      /** Read first header size **/
      /****************************/
		i_AddiHeaderRW_ReadEeprom(1,	/* i_NbOfWordsToRead */
			dw_PCIBoardEepromAddress, w_AnalogInputComponentAddress,	/*  Address of the first header */
			&w_FirstHeaderSize);

		w_FirstHeaderSize = w_FirstHeaderSize >> 4;

      /***************************/
      /** Read number of inputs **/
      /***************************/
		i_AddiHeaderRW_ReadEeprom(1,	/* i_NbOfWordsToRead */
			dw_PCIBoardEepromAddress, w_AnalogInputComponentAddress + 0x06,	/*  Number of inputs for the first modul */
			&w_NumberOfInputs);

		w_NumberOfInputs = w_NumberOfInputs >> 4;

      /***********************/
      /** Read the CJC flag **/
      /***********************/
		i_AddiHeaderRW_ReadEeprom(1,	/* i_NbOfWordsToRead */
			dw_PCIBoardEepromAddress, w_AnalogInputComponentAddress + 0x08,	/*  CJC flag */
			&w_CJCFlag);

		w_CJCFlag = (w_CJCFlag >> 3) & 0x1;	/*  Get only the CJC flag */

      /*******************************/
      /** Read number of gain value **/
      /*******************************/
		i_AddiHeaderRW_ReadEeprom(1,	/* i_NbOfWordsToRead */
			dw_PCIBoardEepromAddress, w_AnalogInputComponentAddress + 0x44,	/*  Number of gain value */
			&w_NumberOfGainValue);

		w_NumberOfGainValue = w_NumberOfGainValue & 0xFF;

      /***********************************/
      /** Compute single header address **/
      /***********************************/
		w_SingleHeaderAddress =
			w_AnalogInputComponentAddress + 0x46 +
			(((w_NumberOfGainValue / 16) + 1) * 2) +
			(6 * w_NumberOfGainValue) +
			(4 * (((w_NumberOfGainValue / 16) + 1) * 2));

      /********************************************/
      /** Read current sources value for input 1 **/
      /********************************************/
		i_AddiHeaderRW_ReadEeprom(1,	/* i_NbOfWordsToRead */
			dw_PCIBoardEepromAddress, w_SingleHeaderAddress,	/* w_EepromStartAddress: Single header address */
			&w_SingleHeaderSize);

		w_SingleHeaderSize = w_SingleHeaderSize >> 4;

      /*************************************/
      /** Read gain factor for the module **/
      /*************************************/
		w_GainFactorAddress = w_AnalogInputComponentAddress;

		for (w_GainIndex = 0; w_GainIndex < w_NumberOfGainValue;
			w_GainIndex++) {
	  /************************************/
	  /** Read gain value for the module **/
	  /************************************/
			i_AddiHeaderRW_ReadEeprom(1,	/* i_NbOfWordsToRead */
				dw_PCIBoardEepromAddress, w_AnalogInputComponentAddress + 70 + (2 * (1 + (w_NumberOfGainValue / 16))) + (0x02 * w_GainIndex),	/*  Gain value */
				&w_GainValue);

			BoardInformations->s_Module[w_ModulCounter].
				w_GainValue[w_GainIndex] = w_GainValue;

#             ifdef PRINT_INFO
			printk("\n Gain value = %d",
				BoardInformations->s_Module[w_ModulCounter].
				w_GainValue[w_GainIndex]);
#             endif

	  /*************************************/
	  /** Read gain factor for the module **/
	  /*************************************/
			i_AddiHeaderRW_ReadEeprom(2,	/* i_NbOfWordsToRead */
				dw_PCIBoardEepromAddress, w_AnalogInputComponentAddress + 70 + ((2 * w_NumberOfGainValue) + (2 * (1 + (w_NumberOfGainValue / 16)))) + (0x04 * w_GainIndex),	/*  Gain factor */
				w_GainFactorValue);

			BoardInformations->s_Module[w_ModulCounter].
				ul_GainFactor[w_GainIndex] =
				(w_GainFactorValue[1] << 16) +
				w_GainFactorValue[0];

#             ifdef PRINT_INFO
			printk("\n w_GainFactorValue [%d] = %lu", w_GainIndex,
				BoardInformations->s_Module[w_ModulCounter].
				ul_GainFactor[w_GainIndex]);
#             endif
		}

      /***************************************************************/
      /** Read current source value for each channels of the module **/
      /***************************************************************/
		for (w_Input = 0; w_Input < w_NumberOfInputs; w_Input++) {
	  /********************************************/
	  /** Read current sources value for input 1 **/
	  /********************************************/
			i_AddiHeaderRW_ReadEeprom(2,	/* i_NbOfWordsToRead */
				dw_PCIBoardEepromAddress,
				(w_Input * w_SingleHeaderSize) +
				w_SingleHeaderAddress + 0x0C, w_CurrentSources);

	  /************************************/
	  /** Save the current sources value **/
	  /************************************/
			BoardInformations->s_Module[w_ModulCounter].
				ul_CurrentSource[w_Input] =
				(w_CurrentSources[0] +
				((w_CurrentSources[1] & 0xFFF) << 16));

#             ifdef PRINT_INFO
			printk("\n Current sources [%d] = %lu", w_Input,
				BoardInformations->s_Module[w_ModulCounter].
				ul_CurrentSource[w_Input]);
#             endif
		}

      /***************************************/
      /** Read the CJC current source value **/
      /***************************************/
		i_AddiHeaderRW_ReadEeprom(2,	/* i_NbOfWordsToRead */
			dw_PCIBoardEepromAddress,
			(w_Input * w_SingleHeaderSize) + w_SingleHeaderAddress +
			0x0C, w_CurrentSources);

      /************************************/
      /** Save the current sources value **/
      /************************************/
		BoardInformations->s_Module[w_ModulCounter].
			ul_CurrentSourceCJC =
			(w_CurrentSources[0] +
			((w_CurrentSources[1] & 0xFFF) << 16));

#          ifdef PRINT_INFO
		printk("\n Current sources CJC = %lu",
			BoardInformations->s_Module[w_ModulCounter].
			ul_CurrentSourceCJC);
#          endif
	}
}